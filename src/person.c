/*
* Name: Chase Counsell
* Project: COMP 5400 Project 4
* File: student.c
* Date: 3/1/2016
* Description: Functions for drawing individual parts of the 3D student
*/
#define MAX_PEOPLE 10
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdlib.h>
#include<GL\glut.h>
#include "person.h"
#include "cube.h"

GLfloat * calculate_joint_location(GLfloat point1_x, GLfloat point1_y, GLfloat point1_z,
								   GLfloat phi, GLfloat psi, GLfloat theta,
								   GLfloat point2_x, GLfloat point2_y, GLfloat point2_z);

enum parts {HEAD, NECK, BODY, LEFT_BICEP, LEFT_FOREARM, RIGHT_BICEP, RIGHT_FOREARM, LEFT_THIGH, LEFT_CALF, RIGHT_THIGH, RIGHT_CALF};

typedef struct Joints
{
	GLfloat head_to_neck[3];
	GLfloat neck_to_body[3];
	GLfloat left_shoulder[3];
	GLfloat left_elbow[3];
	GLfloat right_shoulder[3];
	GLfloat right_elbow[3];
	GLfloat left_hip[3];
	GLfloat left_knee[3];
	GLfloat right_hip[3];
	GLfloat right_knee[3];
}Joints;

Joints joints = { { 0.0, 0.0, 0.0 } };

static int num_people = 0;
static Person people[MAX_PEOPLE];
static int selected_person = 0;

void draw_neck(int skin_color)
{
	GLfloat * neck_scale = people[selected_person].body_parts[NECK].scale;
	GLfloat * neck_angle = people[selected_person].body_parts[NECK].angle;

	glPushMatrix();
	change_color(skin_color);
	glTranslatef(joints.neck_to_body[0], joints.neck_to_body[1], joints.neck_to_body[2]);
	glTranslatef(0.0, neck_scale[1] / 2.0, 0.0);
	glScalef(neck_scale[0], neck_scale[1], neck_scale[2]);
	draw_cube();
	glPopMatrix();

	GLfloat * delta = calculate_joint_location(0.0, neck_scale[1], 0.0,
											   neck_angle[0], neck_angle[1], neck_angle[2],
											   joints.neck_to_body[0], joints.neck_to_body[1], joints.neck_to_body[2]);

	joints.head_to_neck[0] = delta[0];
	joints.head_to_neck[1] = delta[1];
	joints.head_to_neck[2] = delta[2];
}

void draw_hair(void)
{
	GLfloat color_brown[3] = { 0.37, 0.15, 0.02 };
	glPushMatrix();
	glColor3fv(color_brown);
	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_brown);
	glPushMatrix();
	glTranslatef(0.0, 8.25, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glNormal3d(-4.25, -4.25, 0.0);
		glVertex2d(-4.25, -4.25);
		glNormal3d(4.25, -4.25, 0.0);
		glVertex2d(4.25, -4.25);
		glNormal3d(4.25, 4.25, 0.0);
		glVertex2d(4.25, 4.25);
		glNormal3d(-4.25, 4.25, 0.0);
		glVertex2d(-4.25, 4.25);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.25, 4.0, 0.0);
	glRotatef(-90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glNormal3d(-4.25, -1.0, 0.0);
		glVertex2d(-4.25, -1.0);
		glNormal3d(-3.0, -1.0, 0.0);
		glVertex2d(-3.0, -1.0);
		glNormal3d(-3.0, 0.0, 0.0);
		glVertex2d(-3.0, 0.0);
		glNormal3d(0.0, 0.0, 0.0);
		glVertex2d(0.0, 0.0);
		glNormal3d(0.0, 1.0, 0.0);
		glVertex2d(0.0, 1.0);
		glNormal3d(4.25, 1.0, 0.0);
		glVertex2d(4.25, 1.0);
		glNormal3d(4.25, 4.25, 0.0);
		glVertex2d(4.25, 4.25);
		glNormal3d(-4.25, 4.25, 0.0);
		glVertex2d(-4.25, 4.25);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.25, 4.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glNormal3d(4.25, -1.0, 0.0);
		glVertex2d(4.25, -1.0);
		glNormal3d(4.25, 4.25, 0.0);
		glVertex2d(4.25, 4.25);
		glNormal3d(-4.25, 4.25, 0.0);
		glVertex2d(-4.25, 4.25);
		glNormal3d(-4.25, 1.0, 0.0);
		glVertex2d(-4.25, 1.0);
		glNormal3d(0.0, 1.0, 0.0);
		glVertex2d(0.0, 1.0);
		glNormal3d(0.0, 0.0, 0.0);
		glVertex2d(0.0, 0.0);
		glNormal3d(3.0, 0.0, 0.0);
		glVertex2d(3.0, 0.0);
		glNormal3d(3.0, -1.0, 0.0);
		glVertex2d(3.0, -1.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 4.0, -4.25);
	glRotatef(180, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glNormal3d(-4.25, -1.0, 0.0);
		glVertex2d(-4.25, -1.0);
		glNormal3d(4.25, -1.0, 0.0);
		glVertex2d(4.25, -1.0);
		glNormal3d(4.25, 4.25, 0.0);
		glVertex2d(4.25, 4.25);
		glNormal3d(-4.25, 4.25, 0.0);
		glVertex2d(-4.25, 4.25);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 4.0, 4.25);
	glRotatef(0, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glNormal3d(-4.25, 1.0, 0.0);
		glVertex2d(-4.25, 1.0);
		glNormal3d(0.0, 1.0, 0.0);
		glVertex2d(0.0, 1.0);
		glNormal3d(4.25, 3.0, 0.0);
		glVertex2d(4.25, 3.0);
		glNormal3d(4.25, 4.25, 0.0);
		glVertex2d(4.25, 4.25);
		glNormal3d(-4.25, 4.25, 0.0);
		glVertex2d(-4.25, 4.25);
	glEnd();
	glPopMatrix();
	glPopMatrix();
}

void draw_face(void)
{
	glPushMatrix();
	glPushMatrix();
	change_color(COLOR_WHITE);
	glTranslatef(-1.5, 4.1, 4.01);
	glScalef(2.0, 1.0, 1.0);
	square(2);
	glPopMatrix();

	glPushMatrix();
	change_color(COLOR_BLACK);
	glTranslatef(-1.3, 4.0, 4.02);
	glScalef(0.75, 0.75, 1.0);
	square(2);
	glPopMatrix();

	glPushMatrix();
	change_color(COLOR_WHITE);
	glTranslatef(1.5, 4.1, 4.01);
	glScalef(2.0, 1.0, 1.0);
	square(2);
	glPopMatrix();

	glPushMatrix();
	change_color(COLOR_BLACK);
	glTranslatef(1.3, 4.0, 4.02);
	glScalef(0.75, 0.75, 1.0);
	square(2);
	glPopMatrix();

	glPushMatrix();
	change_color(COLOR_BLACK);
	glTranslatef(0.0, 2.0, 4.01);
	glScalef(5.0, 0.25, 1.0);
	square(2);
	glPopMatrix();

	glPopMatrix();
}

void draw_head(int skin_color)
{
	GLfloat * head_scale = people[selected_person].body_parts[HEAD].scale;
	GLfloat * head_angle = people[selected_person].body_parts[HEAD].angle;

	GLfloat light_pos[4] = { 0.0, 0.0, 0.0, 1.0};
	GLfloat spot_dir[3] = {0.0, 0.0, 1.0 };
	draw_neck(skin_color);
	
	glPushMatrix();
	glTranslatef(joints.head_to_neck[0], joints.head_to_neck[1], joints.head_to_neck[2]);
	if (people[selected_person].is_student)
	{
		glRotatef(head_angle[1], 0.0, 1.0, 0.0);
		glRotatef(head_angle[0], 1.0, 0.0, 0.0);
	}
	
	glPushMatrix();
	change_color(skin_color);
	glTranslatef(0.0, head_scale[1] / 2.0, 0.0);
	glScalef(head_scale[0], head_scale[1], head_scale[2]);
	draw_cube();
	
	if (people[selected_person].is_student)
	{
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_dir);
		glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	}
	
	glPopMatrix();

	draw_hair();
	draw_face();
	glPopMatrix();
}

void draw_body(int shirt_color)
{
	GLfloat * body_scale = people[selected_person].body_parts[BODY].scale;
	GLfloat * body_angle = people[selected_person].body_parts[BODY].angle;

	glPushMatrix();
	change_color(shirt_color);
	glScalef(body_scale[0], body_scale[1], body_scale[2]);
	draw_cube();
	glPopMatrix();

	GLfloat * neck_body_joint = calculate_joint_location(0.0, body_scale[1] / 2.0, 0.0, 
												         body_angle[0], body_angle[1], body_angle[2],
												         0.0, 0.0, 0.0);

	joints.neck_to_body[0] = neck_body_joint[0], joints.neck_to_body[1] = neck_body_joint[1], joints.neck_to_body[2] = neck_body_joint[2];

	GLfloat * left_shoulder_joint = calculate_joint_location(body_scale[0] / 2.0, body_scale[1] / 2.0, 0.0,
		                                                     body_angle[0], body_angle[1], body_angle[2], 
		                                                     0.0, 0.0, 0.0);

	joints.left_shoulder[0] = left_shoulder_joint[0], joints.left_shoulder[1] = left_shoulder_joint[1], joints.left_shoulder[2] = left_shoulder_joint[2];
	
	GLfloat * right_shoulder_joint = calculate_joint_location(body_scale[0] / -2.0, body_scale[1] / 2.0, 0.0,
		                                                      body_angle[0], body_angle[1], body_angle[2],
		                                                      0.0, 0.0, 0.0);

	joints.right_shoulder[0] = right_shoulder_joint[0], joints.right_shoulder[1] = right_shoulder_joint[1], joints.right_shoulder[2] = right_shoulder_joint[2];
	
	GLfloat * left_hip_joint = calculate_joint_location(body_scale[0] / 4.0, body_scale[1] / -2.0, 0.0,
		                                                body_angle[0], body_angle[1], body_angle[2],
		                                                0.0, 0.0, 0.0);

	joints.left_hip[0] = left_hip_joint[0], joints.left_hip[1] = left_hip_joint[1], joints.left_hip[2] = left_hip_joint[2];
	
	GLfloat * right_hip_joint = calculate_joint_location(body_scale[0] / -4.0, body_scale[1] / -2.0, 0.0,
		                                                 body_angle[0], body_angle[1], body_angle[2],
		                                                 0.0, 0.0, 0.0);

	joints.right_hip[0] = right_hip_joint[0], joints.right_hip[1] = right_hip_joint[1], joints.right_hip[2] = right_hip_joint[2];
}

void draw_left_hand(int skin_color)
{
	glPushMatrix();
	change_color(skin_color);
	glTranslatef(0.0, -6.0, -2.0);
	glScalef(4.0, 2.0, 4.0);
	draw_cube();
	glPopMatrix();
}

void draw_left_bicep(int shirt_color)
{
	GLfloat * lbicep_scale = people[selected_person].body_parts[LEFT_BICEP].scale;
	GLfloat * lbicep_angle = people[selected_person].body_parts[LEFT_BICEP].angle;

	glPushMatrix();
	change_color(shirt_color);
	glTranslatef(joints.left_shoulder[0], joints.left_shoulder[1], joints.left_shoulder[2]);
	glRotatef(lbicep_angle[2], 0.0, 0.0, 1.0);
	glTranslatef(lbicep_scale[0] / 2.0, lbicep_scale[1] / -2.0, 0.0);
	glScalef(lbicep_scale[0], lbicep_scale[1], lbicep_scale[2]);
	draw_cube();
	glPopMatrix();

	GLfloat * left_elbow_joint = calculate_joint_location(lbicep_scale[0] / 2.0, -lbicep_scale[1], lbicep_scale[2] / 2.0, 
		                                                  lbicep_angle[0], lbicep_angle[1], lbicep_angle[2],
		                                                  joints.left_shoulder[0], joints.left_shoulder[1], joints.left_shoulder[2]);

	joints.left_elbow[0] = left_elbow_joint[0], joints.left_elbow[1] = left_elbow_joint[1], joints.left_elbow[2] = left_elbow_joint[2];
}

void draw_left_forearm(int shirt_color, int skin_color)
{
	GLfloat * lforearm_scale = people[selected_person].body_parts[LEFT_FOREARM].scale;
	GLfloat * lforearm_angle = people[selected_person].body_parts[LEFT_FOREARM].angle;

	glPushMatrix();
	change_color(shirt_color);
	glTranslatef(joints.left_elbow[0], joints.left_elbow[1], joints.left_elbow[2]);
	glRotatef(lforearm_angle[2] = people[selected_person].body_parts[LEFT_BICEP].angle[2], 0.0, 0.0, 1.0);
	glRotatef(lforearm_angle[0], 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, -2.5, -2.0);
	glScalef(lforearm_scale[0], lforearm_scale[1], lforearm_scale[2]);
	draw_cube();
	glPopMatrix();
	draw_left_hand(skin_color);
	glPopMatrix();
}

void draw_left_arm(int shirt_color, int skin_color)
{
	draw_left_bicep(shirt_color);
	draw_left_forearm(shirt_color, skin_color);
}

void draw_phone(void)
{
	glPushMatrix();
	change_color(COLOR_GRAY);
	glTranslatef(0.0, -1.0, 0.0);
	glRotatef(90.0, 0, 1, 0);
	glRotatef(90.0, 0, 0, 1);
	glTranslatef(-1.75, 0.0, 0.0);

	glPushMatrix();
	glScalef(3.5, 6.0, 1.0);
	draw_cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.2, 0.51);
	glScalef(3.0, 5.0, 1.0);
	change_color(COLOR_WHITE);
	square(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.15, 2.35, 0.52);
	glScalef(0.5, 0.5, 1.0);
	change_color(COLOR_RED);
	square(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.383, 2.35, 0.52);
	glScalef(0.5, 0.5, 1.0);
	change_color(COLOR_BROWN);
	square(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.383, 2.35, 0.52);
	glScalef(0.5, 0.5, 1.0);
	change_color(COLOR_GRAY);
	square(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.15, 2.35, 0.52);
	glScalef(0.5, 0.5, 1.0);
	change_color(COLOR_ORANGE);
	square(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.15, 1.275, 0.52);
	glScalef(0.5, 0.5, 1.0);
	change_color(COLOR_BLUE);
	square(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.383, 1.275, 0.52);
	glScalef(0.5, 0.5, 1.0);
	change_color(COLOR_ORANGE);
	square(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.383, 1.275, 0.52);
	glScalef(0.5, 0.5, 1.0);
	change_color(COLOR_GREEN);
	square(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.15, 1.275, 0.52);
	glScalef(0.5, 0.5, 1.0);
	change_color(COLOR_RED);
	square(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.15, 0.2, 0.52);
	glScalef(0.5, 0.5, 1.0);
	change_color(COLOR_BLUE);
	square(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.383, 0.2, 0.52);
	glScalef(0.5, 0.5, 1.0);
	change_color(COLOR_GRAY);
	square(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.383, 0.2, 0.52);
	glScalef(0.5, 0.5, 1.0);
	change_color(COLOR_GREEN);
	square(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.15, 0.2, 0.52);
	glScalef(0.5, 0.5, 1.0);
	change_color(COLOR_BROWN);
	square(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.15, -0.875, 0.52);
	glScalef(0.5, 0.5, 1.0);
	change_color(COLOR_ORANGE);
	square(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.383, -0.875, 0.52);
	glScalef(0.5, 0.5, 1.0);
	change_color(COLOR_BLACK);
	square(2);
	glPopMatrix();

	glPopMatrix();
}

void draw_right_hand(int skin_color)
{
	glPushMatrix();
	change_color(skin_color);
	glTranslatef(0.0, -6.0, -2.0);
	glPushMatrix();
	glScalef(4.0, 2.0, 4.0);
	draw_cube();
	glPopMatrix();
	draw_phone();
	glPopMatrix();
}

void draw_right_bicep(int shirt_color)
{
	GLfloat * rbicep_scale = people[selected_person].body_parts[RIGHT_BICEP].scale;
	GLfloat * rbicep_angle = people[selected_person].body_parts[RIGHT_BICEP].angle;

	glPushMatrix();
	change_color(shirt_color);
	glTranslatef(joints.right_shoulder[0], joints.right_shoulder[1], joints.right_shoulder[2]);
	glRotatef(rbicep_angle[2], 0.0, 0.0, 1.0);
	glTranslatef(rbicep_scale[0] / -2.0, rbicep_scale[1] / -2.0, 0.0);
	glScalef(rbicep_scale[0], rbicep_scale[1], rbicep_scale[2]);
	draw_cube();
	glPopMatrix();

	GLfloat * right_elbow_joint = calculate_joint_location(rbicep_scale[0] / -2.0, -rbicep_scale[1], rbicep_scale[2] / 2.0,
		                                                   rbicep_angle[0], rbicep_angle[1], rbicep_angle[2],
		                                                   joints.right_shoulder[0], joints.right_shoulder[1], joints.right_shoulder[2]);

	joints.right_elbow[0] = right_elbow_joint[0], joints.right_elbow[1] = right_elbow_joint[1], joints.right_elbow[2] = right_elbow_joint[2];
}

void draw_right_forearm(int shirt_color, int skin_color)
{
	GLfloat * rforearm_scale = people[selected_person].body_parts[RIGHT_FOREARM].scale;
	GLfloat * rforearm_angle = people[selected_person].body_parts[RIGHT_FOREARM].angle;

	glPushMatrix();
	change_color(shirt_color);
	glTranslatef(joints.right_elbow[0], joints.right_elbow[1], joints.right_elbow[2]);
	glRotatef(rforearm_angle[2] = people[selected_person].body_parts[RIGHT_BICEP].angle[2], 0.0, 0.0, 1.0);
	glRotatef(rforearm_angle[0], 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, -2.5, -2.0);
	glScalef(rforearm_scale[0], rforearm_scale[1], rforearm_scale[2]);
	draw_cube();
	glPopMatrix();
	draw_right_hand(skin_color);
	glPopMatrix();
}

void draw_right_arm(int shirt_color, int skin_color)
{
	draw_right_bicep(shirt_color);
	draw_right_forearm(shirt_color, skin_color);
}

void draw_left_foot(int shoe_color)
{
	glPushMatrix();
	change_color(shoe_color);
	glTranslatef(0.0, -6.0, 3.0);
	glScalef(4.0, 2.0, 6.0);
	draw_cube();
	glPopMatrix();
}

void draw_left_thigh(int pants_color)
{
	GLfloat * lthigh_scale = people[selected_person].body_parts[LEFT_THIGH].scale;
	GLfloat * lthigh_angle = people[selected_person].body_parts[LEFT_THIGH].angle;

	glPushMatrix();
	change_color(pants_color);
	glTranslatef(joints.left_hip[0], joints.left_hip[1], joints.left_hip[2]);
	glRotatef(lthigh_angle[0], 1.0, 0.0, 0.0);
	glTranslatef(0.0, lthigh_scale[1] / -2.0, 0.0);
	glScalef(lthigh_scale[0], lthigh_scale[1], lthigh_scale[2]);
	draw_cube();
	glPopMatrix();

	GLfloat * left_knee_joint = calculate_joint_location(0.0, -lthigh_scale[1], lthigh_scale[2] / -2.0,
		                                                 lthigh_angle[0], lthigh_angle[1], lthigh_angle[2],
		                                                 joints.left_hip[0], joints.left_hip[1], joints.left_hip[2]);

	joints.left_knee[0] = left_knee_joint[0], joints.left_knee[1] = left_knee_joint[1], joints.left_knee[2] = left_knee_joint[2];
}

void draw_left_calf(int pants_color, int shoe_color)
{
	GLfloat * lcalf_scale = people[selected_person].body_parts[LEFT_CALF].scale;
	GLfloat * lcalf_angle = people[selected_person].body_parts[LEFT_CALF].angle;

	glPushMatrix();
	change_color(pants_color);
	glTranslatef(joints.left_knee[0], joints.left_knee[1], joints.left_knee[2]);
	glRotatef(lcalf_angle[0], 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, -2.5, 2.0);
	glScalef(lcalf_scale[0], lcalf_scale[1], lcalf_scale[2]);
	draw_cube();
	glPopMatrix();
	draw_left_foot(shoe_color);
	glPopMatrix();
}

void draw_left_leg(int pants_color, int shoe_color)
{
	draw_left_thigh(pants_color);
	draw_left_calf(pants_color, shoe_color);
}

void draw_right_foot(int shoe_color)
{
	glPushMatrix();
	change_color(shoe_color);
	glTranslatef(0.0, -6.0, 3.0);
	glScalef(4.0, 2.0, 6.0);
	draw_cube();
	glPopMatrix();
}

void draw_right_thigh(int pants_color)
{
	GLfloat * rthigh_scale = people[selected_person].body_parts[RIGHT_THIGH].scale;
	GLfloat * rthigh_angle = people[selected_person].body_parts[RIGHT_THIGH].angle;

	glPushMatrix();
	change_color(pants_color);
	glTranslatef(joints.right_hip[0], joints.right_hip[1], joints.right_hip[2]);
	glRotatef(rthigh_angle[0], 1.0, 0.0, 0.0);
	glTranslatef(0.0, rthigh_scale[1] / -2.0, 0.0);
	glScalef(rthigh_scale[0], rthigh_scale[1], rthigh_scale[2]);
	draw_cube();
	glPopMatrix();

	GLfloat * right_knee_joint = calculate_joint_location(0.0, -rthigh_scale[1], rthigh_scale[2] / -2.0,
		                                                  rthigh_angle[0], rthigh_angle[1], rthigh_angle[2],
		                                                  joints.right_hip[0], joints.right_hip[1], joints.right_hip[2]);

	joints.right_knee[0] = right_knee_joint[0], joints.right_knee[1] = right_knee_joint[1], joints.right_knee[2] = right_knee_joint[2];
}

void draw_right_calf(int pants_color, int shoe_color)
{
	GLfloat * rcalf_scale = people[selected_person].body_parts[RIGHT_CALF].scale;
	GLfloat * rcalf_angle = people[selected_person].body_parts[RIGHT_CALF].angle;

	glPushMatrix();
	change_color(pants_color);
	glTranslatef(joints.right_knee[0], joints.right_knee[1], joints.right_knee[2]);
	glRotatef(rcalf_angle[0], 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, rcalf_scale[1] / -2.0, rcalf_scale[2] / 2.0);
	glScalef(rcalf_scale[0], rcalf_scale[1], rcalf_scale[2]);
	draw_cube();
	glPopMatrix();
	draw_right_foot(shoe_color);
	glPopMatrix();
}

void draw_right_leg(int pants_color, int shoe_color)
{
	draw_right_thigh(pants_color);
	draw_right_calf(pants_color, shoe_color);
}

void draw_backpack(void)
{
	glPushMatrix();
	change_color(COLOR_GRAY);
	glTranslatef(0.0, 2.0, -3.5);
	glScalef(8.0, 8.0, 3.0);
	draw_cube();
	glPopMatrix();

	glPushMatrix();
	change_color(COLOR_RED);
	glTranslatef(0.0, 1.0, -5.5);
	glScalef(6.0, 4.0, 1.0);
	draw_cube();
	glPopMatrix();

	glPushMatrix();
	change_color(COLOR_GRAY);
	glTranslatef(4.0, 3.0, 2.5);
	glScalef(1.0, 6.5, 0.5);
	draw_cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.25, -1.0, 0.0);
	glRotatef(-15.0, 1.0, 0.0, 0.0);
	glScalef(0.5, 1.0, 5.0);
	draw_cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.0, 6.25, -0.5);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glScalef(1.0, 6.0, 0.5);
	draw_cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.0, 3.0, 2.5);
	glScalef(1.0, 6.5, 0.5);
	draw_cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.25, -1.0, 0.0);
	glRotatef(-15.0, 1.0, 0.0, 0.0);
	glScalef(0.5, 1.0, 5.0);
	draw_cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.0, 6.25, -0.5);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glScalef(1.0, 6.0, 0.5);
	draw_cube();
	glPopMatrix();
}

void initialize_person(Person * person)
{
	Body_Part body = { { 8.0, 12.0, 4.0 },{ 0.0, 0.0, 0.0} };
	person->body_parts[BODY] = body;

	Body_Part neck = { { 4.0, 0.5, 4.0 },{ 0.0, 0.0, 0.0 } };
	person->body_parts[NECK] = neck;

	Body_Part head = { { 8.0, 8.0, 8.0 },{ 0.0, 0.0, 0.0 } };
	person->body_parts[HEAD] = head;

	Body_Part l_bicep = { { 4.0, 5.0, 4.0 },{ 0.0, 0.0, 0.0 } };
	person->body_parts[LEFT_BICEP] = l_bicep;

	Body_Part r_bicep = { { 4.0, 5.0, 4.0 },{ 0.0, 0.0, 0.0 } };
	person->body_parts[RIGHT_BICEP] = r_bicep;

	Body_Part l_forearm = { { 4.0, 5.0, 4.0 },{ 0.0, 0.0, 0.0 } };
	person->body_parts[LEFT_FOREARM] = l_forearm;

	Body_Part r_forearm = { { 4.0, 5.0, 4.0 },{ 0.0, 0.0, 0.0 } };
	person->body_parts[RIGHT_FOREARM] = r_forearm;

	Body_Part l_thigh = { { 4.0, 5.0, 4.0 },{ 0.0, 0.0, 0.0 } };
	person->body_parts[LEFT_THIGH] = l_thigh;

	Body_Part l_calf = { { 4.0, 5.0, 4.0 },{ 0.0, 0.0, 0.0 } };
	person->body_parts[LEFT_CALF] = l_calf;

	Body_Part r_thigh = { { 4.0, 5.0, 4.0 },{ 0.0, 0.0, 0.0 } };
	person->body_parts[RIGHT_THIGH] = r_thigh;

	Body_Part r_calf = { { 4.0, 5.0, 4.0 },{ 0.0, 0.0, 0.0 } };
	person->body_parts[RIGHT_CALF] = r_calf;
}

void create_student(int skin_color, int shirt_color, int pants_color, int shoe_color)
{
	if (num_people < MAX_PEOPLE)
	{
		Person student = { 1, { -100.0, 0.0, 0.0, 1.0 }, 0.1, { 0.0, 180.0, 0.0 }, {skin_color, shirt_color, pants_color, shoe_color} };
		initialize_person(&student);
		people[num_people++] = student;
	}
}

void create_bystander(int skin_color, int shirt_color, int pants_color, int shoe_color)
{
	if (num_people < MAX_PEOPLE)
	{
		Person bystander = { 0, { -100.0, 0.0, 0.0, 1.0 }, 0.1, { 0.0, 180.0, 0.0 }, { skin_color, shirt_color, pants_color, shoe_color } };
		initialize_person(&bystander);
		people[num_people++] = bystander;
	}
}

void draw_person(void)
{
	glTranslatef(people[selected_person].position[0], people[selected_person].position[1], people[selected_person].position[2]);
	glScalef(people[selected_person].scale, people[selected_person].scale, people[selected_person].scale);
	glRotatef(people[selected_person].angle[1], 0.0, 1.0, 0.0);
	glTranslatef(0.0, 18.0, 0.0);

	draw_body(people[selected_person].colors[1]);
	draw_head(people[selected_person].colors[0]);
	draw_left_arm(people[selected_person].colors[1], people[selected_person].colors[0]);
	draw_right_arm(people[selected_person].colors[1], people[selected_person].colors[0]);
	draw_left_leg(people[selected_person].colors[2], people[selected_person].colors[3]);
	draw_right_leg(people[selected_person].colors[2], people[selected_person].colors[3]);
	if (people[selected_person].is_student) draw_backpack();
}

void rotate_person(GLfloat phi, GLfloat psi)
{
	people[selected_person].angle[0] = (int)(people[selected_person].angle[0] + phi) % 360;
	people[selected_person].angle[1] = (int)(people[selected_person].angle[1] + psi) % 360;
}

void translate_person(GLfloat delta)
{
	people[selected_person].position[0] += delta * sin(people[selected_person].angle[1] * (M_PI / 180));
	people[selected_person].position[2] += delta * cos(people[selected_person].angle[1] * (M_PI / 180));
}

void scale_person(GLfloat factor)
{
	people[selected_person].scale = factor;
}

void rotate_head(GLfloat phi, GLfloat psi)
{
	GLfloat * head_angle = people[selected_person].body_parts[HEAD].angle;
	if (abs((int)(head_angle[0] + phi) % 360) < 45)
		head_angle[0] = (int)(head_angle[0] + phi) % 360;
	if (abs((int)(head_angle[1] + psi) % 360) < 90)
		head_angle[1] = (int)(head_angle[1] + psi) % 360;
}

GLfloat * get_position(void)
{
	return people[selected_person].position;
}

void select_person(int person)
{
	if (person < num_people)
		selected_person = person;
}

int get_selected_person(void)
{
	return selected_person;
}

Person * get_people(void)
{
	return people;
}

int get_num_people(void)
{
	return num_people;
}

void reset_person(void)
{
	Person initial_person = { 1,{ -100.0, 0.0, 0.0, 1.0 }, 1.0,{ 0.0, 180.0 },{ 0.0, 0.0 } };
	if (!people[selected_person].is_student) initial_person.is_student = 0;
	people[selected_person] = initial_person;
	glLoadIdentity();
}

GLfloat * calculate_joint_location(GLfloat point1_x, GLfloat point1_y, GLfloat point1_z, 
							  GLfloat phi, GLfloat psi, GLfloat theta,
							  GLfloat point2_x, GLfloat point2_y, GLfloat point2_z)
{
	GLfloat joint_x = point1_x * (cos(psi * M_PI / 180) * cos(theta * M_PI / 180)) +
		              point1_y * (-cos(psi * M_PI / 180) * sin(theta * M_PI / 180)) +
					  point1_z * (sin(psi* M_PI / 180));

	GLfloat joint_y = point1_x * (sin(phi * M_PI / 180) * cos(psi * M_PI / 180) * cos(theta * M_PI / 180) + cos(phi * M_PI / 180) * sin(theta * M_PI / 180)) +
		              point1_y * (-sin(phi * M_PI / 180) * sin(psi * M_PI / 180) * sin(theta * M_PI / 180) + cos(phi * M_PI / 180) * cos(theta * M_PI / 180)) +
		              point1_z * (-sin(phi * M_PI / 180) * cos(psi * M_PI / 180));

	GLfloat joint_z = point1_x * (-cos(phi * M_PI / 180) * sin(psi * M_PI / 180) * cos(theta * M_PI / 180) + sin(phi * M_PI / 180) * sin(theta * M_PI / 180)) +
		              point1_y * (cos(phi * M_PI / 180) * sin(psi * M_PI / 180) * sin(theta * M_PI / 180) + sin(phi * M_PI / 180) * cos(theta * M_PI / 180)) +
		              point1_z * (cos(phi * M_PI / 180) * cos(psi * M_PI / 180));

	GLfloat joint_location[3] = { joint_x + point2_x, joint_y + point2_y, joint_z + point2_z };

	return joint_location;
}

void calculate_bounds(void)
{

}