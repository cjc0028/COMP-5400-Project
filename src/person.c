/*
* Name: Chase Counsell
* Project: COMP 5400 Project 4
* File: student.c
* Date: 3/1/2016
* Description: Functions for drawing individual parts of the 3D student
*/
#define MAX_PEOPLE 100
#define NUM_BODY_PARTS 11
#define _USE_MATH_DEFINES
#include<math.h>
#include<string.h>
#include<stdarg.h>
#include<stdio.h>
#include<stdlib.h>
#include<GL\glut.h>
#include "person.h"
#include "camera.h"
#include "shapes.h"
#include "command_processor.h"

GLfloat * calculate_joint_location(GLfloat point1_x, GLfloat point1_y, GLfloat point1_z,
								   GLfloat phi, GLfloat psi, GLfloat theta,
								   GLfloat point2_x, GLfloat point2_y, GLfloat point2_z);
static void calculate_bounds(GLfloat * scale, GLfloat * angle, GLfloat * delta);
static void draw_bounds(void);

enum parts {HEAD, NECK, BODY, LEFT_BICEP, LEFT_FOREARM, RIGHT_BICEP, RIGHT_FOREARM, LEFT_THIGH, LEFT_CALF, RIGHT_THIGH, RIGHT_CALF};
char * str_parts[NUM_BODY_PARTS] = { "HEAD", "NECK", "BODY", "LEFT_BICEP", 
									 "LEFT_FOREARM", "RIGHT_BICEP", "RIGHT_FOREARM", 
									 "LEFT_THIGH", "LEFT_CALF", "RIGHT_THIGH", "RIGHT_CALF"};

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

static const GLfloat initial_pos[4] = { -100.0, 18.0, 0.0, 1.0 };
static const GLfloat initial_angle[3] = { 0.0, 180.0, 0.0 };
static const GLfloat initial_scale = 0.1;

void initialize_people(void)
{
	add_command("person", &person_commands);
	add_sub_command("person", "help");
	add_sub_command("person", "list");
	add_sub_command("person", "create");
	add_sub_command("person", "select");
	add_sub_command("person", "set");
	add_sub_command("person", "remove");
}

void draw_neck(int skin_color)
{
	GLfloat * neck_scale = people[selected_person].body_parts[NECK].scale;
	GLfloat * neck_angle = people[selected_person].body_parts[NECK].angle;

	glPushMatrix();
	change_color(skin_color);
	glTranslatef(joints.neck_to_body[0], joints.neck_to_body[1], joints.neck_to_body[2]);
	glRotatef(neck_angle[2], 0.0, 0.0, 1.0);
	glRotatef(neck_angle[1], 0.0, 1.0, 0.0);
	glRotatef(neck_angle[0], 1.0, 0.0, 0.0);
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

	delta = joints.neck_to_body;
	delta[1] += neck_scale[1] / 2.0;
	calculate_bounds(neck_scale, neck_angle, delta);
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

void draw_head(int skin_color, int person)
{
	GLfloat * head_scale = people[selected_person].body_parts[HEAD].scale;
	GLfloat * head_angle = people[selected_person].body_parts[HEAD].angle;

	GLfloat light_pos[4] = { 0.0, 0.0, 0.0, 1.0};
	GLfloat spot_dir[3] = {0.0, 0.0, 1.0 };
	draw_neck(skin_color);
	
	glPushMatrix();
	glTranslatef(joints.head_to_neck[0], joints.head_to_neck[1], joints.head_to_neck[2]);
	if (person == selected_person)
	{
		glRotatef(head_angle[2], 0.0, 0.0, 1.0);
		glRotatef(head_angle[1], 0.0, 1.0, 0.0);
		glRotatef(head_angle[0], 1.0, 0.0, 0.0);
	}
	
	glPushMatrix();
	change_color(skin_color);
	glTranslatef(0.0, head_scale[1] / 2.0, 0.0);
	glScalef(head_scale[0], head_scale[1], head_scale[2]);
	draw_cube();
	

	if (person == 0)
	{
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_dir);
		glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	}
	
	glPopMatrix();

	draw_hair();
	draw_face();
	glPopMatrix();

	GLfloat * delta = joints.head_to_neck;
	delta[1] += (head_scale[1] / 2.0);

	calculate_bounds(head_scale, head_angle, delta);
}

void draw_body(int shirt_color)
{
	GLfloat * body_scale = people[selected_person].body_parts[BODY].scale;
	GLfloat * body_angle = people[selected_person].body_parts[BODY].angle;

	glPushMatrix();
	change_color(shirt_color);
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(body_angle[2], 0.0, 0.0, 1.0);
	glRotatef(body_angle[1], 0.0, 1.0, 0.0);
	glRotatef(body_angle[0], 1.0, 0.0, 0.0);
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

	GLfloat delta[3] = { 0.0, 0.0, 0.0 };
	calculate_bounds(body_scale, body_angle, delta);
}

void draw_left_hand(int skin_color)
{
	glPushMatrix();
	change_color(skin_color);
	glTranslatef(0.0, -6.0, -2.0);
	glScalef(4.0, 2.0, 4.0);
	draw_cube();
	glPopMatrix();

	GLfloat scale[3] = { 4.0, 2.0, 4.0 };
	GLfloat * angle = people[selected_person].body_parts[LEFT_FOREARM].angle;
	GLfloat delta[3] = { 0.0 + joints.left_elbow[0], -6.0 + joints.left_elbow[1], -2.0 + joints.left_elbow[2] };

	calculate_bounds(scale, angle, delta);
}

void draw_left_bicep(int shirt_color)
{
	GLfloat * lbicep_scale = people[selected_person].body_parts[LEFT_BICEP].scale;
	GLfloat * lbicep_angle = people[selected_person].body_parts[LEFT_BICEP].angle;

	glPushMatrix();
	change_color(shirt_color);
	glTranslatef(joints.left_shoulder[0], joints.left_shoulder[1], joints.left_shoulder[2]);
	glRotatef(lbicep_angle[2], 0.0, 0.0, 1.0);
	glRotatef(lbicep_angle[1], 0.0, 1.0, 0.0);
	glRotatef(lbicep_angle[0], 1.0, 0.0, 0.0);
	glTranslatef(lbicep_scale[0] / 2.0, lbicep_scale[1] / -2.0, 0.0);
	glScalef(lbicep_scale[0], lbicep_scale[1], lbicep_scale[2]);
	draw_cube();
	glPopMatrix();

	GLfloat * left_elbow_joint = calculate_joint_location(lbicep_scale[0] / 2.0, -lbicep_scale[1], lbicep_scale[2] / 2.0, 
		                                                  lbicep_angle[0], lbicep_angle[1], lbicep_angle[2],
		                                                  joints.left_shoulder[0], joints.left_shoulder[1], joints.left_shoulder[2]);

	joints.left_elbow[0] = left_elbow_joint[0], joints.left_elbow[1] = left_elbow_joint[1], joints.left_elbow[2] = left_elbow_joint[2];

	GLfloat  * delta = joints.left_shoulder;
	delta[0] += lbicep_scale[0] / 2.0;
	delta[1] += lbicep_scale[1] / -2.0;
	calculate_bounds(lbicep_scale, lbicep_angle, delta);
}

void draw_left_forearm(int shirt_color, int skin_color)
{
	GLfloat * lforearm_scale = people[selected_person].body_parts[LEFT_FOREARM].scale;
	GLfloat * lforearm_angle = people[selected_person].body_parts[LEFT_FOREARM].angle;

	glPushMatrix();
	change_color(shirt_color);
	glTranslatef(joints.left_elbow[0], joints.left_elbow[1], joints.left_elbow[2]);
	glRotatef(lforearm_angle[2] + people[selected_person].body_parts[LEFT_BICEP].angle[2], 0.0, 0.0, 1.0);
	glRotatef(lforearm_angle[1] + people[selected_person].body_parts[LEFT_BICEP].angle[1], 0.0, 1.0, 0.0);
	glRotatef(lforearm_angle[0] + people[selected_person].body_parts[LEFT_BICEP].angle[0], 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, lforearm_scale[1] / -2.0, lforearm_scale[2] / -2.0);
	glScalef(lforearm_scale[0], lforearm_scale[1], lforearm_scale[2]);
	draw_cube();
	glPopMatrix();
	draw_left_hand(skin_color);
	glPopMatrix();

	GLfloat * delta = joints.left_elbow;
	delta[1] += lforearm_scale[1] / -2.0;
	delta[2] += lforearm_scale[2] / -2.0;
	calculate_bounds(lforearm_scale, lforearm_angle, delta);
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

	GLfloat scale[3] = { 4.0, 2.0, 4.0 };
	GLfloat * angle = people[selected_person].body_parts[RIGHT_FOREARM].angle;
	GLfloat delta[3] = { 0.0, -6.0, -2.0 };

	calculate_bounds(scale, angle, delta);
}

void draw_right_bicep(int shirt_color)
{
	GLfloat * rbicep_scale = people[selected_person].body_parts[RIGHT_BICEP].scale;
	GLfloat * rbicep_angle = people[selected_person].body_parts[RIGHT_BICEP].angle;

	glPushMatrix();
	change_color(shirt_color);
	glTranslatef(joints.right_shoulder[0], joints.right_shoulder[1], joints.right_shoulder[2]);
	glRotatef(rbicep_angle[2], 0.0, 0.0, 1.0);
	glRotatef(rbicep_angle[1], 0.0, 1.0, 0.0);
	glRotatef(rbicep_angle[0], 1.0, 0.0, 0.0);
	glTranslatef(rbicep_scale[0] / -2.0, rbicep_scale[1] / -2.0, 0.0);
	glScalef(rbicep_scale[0], rbicep_scale[1], rbicep_scale[2]);
	draw_cube();
	glPopMatrix();

	GLfloat * right_elbow_joint = calculate_joint_location(rbicep_scale[0] / -2.0, -rbicep_scale[1], rbicep_scale[2] / 2.0,
		                                                   rbicep_angle[0], rbicep_angle[1], rbicep_angle[2],
		                                                   joints.right_shoulder[0], joints.right_shoulder[1], joints.right_shoulder[2]);

	joints.right_elbow[0] = right_elbow_joint[0], joints.right_elbow[1] = right_elbow_joint[1], joints.right_elbow[2] = right_elbow_joint[2];

	GLfloat * delta = joints.right_shoulder;
	delta[0] += rbicep_scale[0] / -2.0;
	delta[1] += rbicep_scale[1] / -2.0;
	calculate_bounds(rbicep_scale, rbicep_angle, delta);
}

void draw_right_forearm(int shirt_color, int skin_color)
{
	GLfloat * rforearm_scale = people[selected_person].body_parts[RIGHT_FOREARM].scale;
	GLfloat * rforearm_angle = people[selected_person].body_parts[RIGHT_FOREARM].angle;

	glPushMatrix();
	change_color(shirt_color);
	glTranslatef(joints.right_elbow[0], joints.right_elbow[1], joints.right_elbow[2]);
	glRotatef(rforearm_angle[2] + people[selected_person].body_parts[RIGHT_BICEP].angle[2], 0.0, 0.0, 1.0);
	glRotatef(rforearm_angle[1] + people[selected_person].body_parts[RIGHT_BICEP].angle[1], 0.0, 1.0, 0.0);
	glRotatef(rforearm_angle[0] + people[selected_person].body_parts[RIGHT_BICEP].angle[0], 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, rforearm_scale[1] / -2.0, rforearm_scale[2] / -2.0);
	glScalef(rforearm_scale[0], rforearm_scale[1], rforearm_scale[2]);
	draw_cube();
	glPopMatrix();
	draw_right_hand(skin_color);
	glPopMatrix();

	GLfloat * delta = joints.right_elbow;
	delta[1] += rforearm_scale[1] / -2.0;
	delta[2] += rforearm_scale[2] / -2.0;
	calculate_bounds(rforearm_scale, rforearm_angle, delta);
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

	GLfloat scale[3] = { 4.0, 2.0, 6.0 };
	GLfloat * angle = people[selected_person].body_parts[LEFT_CALF].angle;
	GLfloat delta[3] = { 0.0 + joints.left_knee[0], -6.0 + joints.left_knee[1], 3.0 + joints.left_knee[2] };

	calculate_bounds(scale, angle, delta);
}

void draw_left_thigh(int pants_color)
{
	GLfloat * lthigh_scale = people[selected_person].body_parts[LEFT_THIGH].scale;
	GLfloat * lthigh_angle = people[selected_person].body_parts[LEFT_THIGH].angle;

	glPushMatrix();
	change_color(pants_color);
	glTranslatef(joints.left_hip[0], joints.left_hip[1], joints.left_hip[2]);
	glRotatef(lthigh_angle[2], 0.0, 0.0, 1.0);
	glRotatef(lthigh_angle[1], 0.0, 1.0, 0.0);
	glRotatef(lthigh_angle[0], 1.0, 0.0, 0.0);
	glTranslatef(0.0, lthigh_scale[1] / -2.0, 0.0);
	glScalef(lthigh_scale[0], lthigh_scale[1], lthigh_scale[2]);
	draw_cube();
	glPopMatrix();

	GLfloat * left_knee_joint = calculate_joint_location(0.0, -lthigh_scale[1], lthigh_scale[2] / -2.0,
		                                                 lthigh_angle[0], lthigh_angle[1], lthigh_angle[2],
		                                                 joints.left_hip[0], joints.left_hip[1], joints.left_hip[2]);

	joints.left_knee[0] = left_knee_joint[0], joints.left_knee[1] = left_knee_joint[1], joints.left_knee[2] = left_knee_joint[2];

	GLfloat * delta = joints.left_hip;
	delta[1] += lthigh_scale[1] / -2.0;
	
	calculate_bounds(lthigh_scale, lthigh_angle, delta);
}

void draw_left_calf(int pants_color, int shoe_color)
{
	GLfloat * lcalf_scale = people[selected_person].body_parts[LEFT_CALF].scale;
	GLfloat * lcalf_angle = people[selected_person].body_parts[LEFT_CALF].angle;

	glPushMatrix();
	change_color(pants_color);
	glTranslatef(joints.left_knee[0], joints.left_knee[1], joints.left_knee[2]);
	glRotatef(lcalf_angle[2] + people[selected_person].body_parts[LEFT_THIGH].angle[2], 0.0, 0.0, 1.0);
	glRotatef(lcalf_angle[1] + people[selected_person].body_parts[LEFT_THIGH].angle[1], 0.0, 1.0, 0.0);
	glRotatef(lcalf_angle[0] + people[selected_person].body_parts[LEFT_THIGH].angle[0], 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, lcalf_scale[1] / -2.0, lcalf_scale[2] / 2.0);
	glScalef(lcalf_scale[0], lcalf_scale[1], lcalf_scale[2]);
	draw_cube();
	glPopMatrix();
	draw_left_foot(shoe_color);
	glPopMatrix();

	GLfloat * delta = joints.left_knee;
	delta[1] += lcalf_scale[1] / -2.0;
	delta[2] += lcalf_scale[2] / 2.0;

	calculate_bounds(lcalf_scale, lcalf_angle, delta);
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

	GLfloat scale[3] = { 4.0, 2.0, 6.0 };
	GLfloat * angle = people[selected_person].body_parts[RIGHT_CALF].angle;
	GLfloat delta[3] = { 0.0 + joints.right_knee[0], -6.0 + joints.right_knee[1], 3.0 + joints.right_knee[2] };

	calculate_bounds(scale, angle, delta);
}

void draw_right_thigh(int pants_color)
{
	GLfloat * rthigh_scale = people[selected_person].body_parts[RIGHT_THIGH].scale;
	GLfloat * rthigh_angle = people[selected_person].body_parts[RIGHT_THIGH].angle;

	glPushMatrix();
	change_color(pants_color);
	glTranslatef(joints.right_hip[0], joints.right_hip[1], joints.right_hip[2]);
	glRotatef(rthigh_angle[2], 0.0, 0.0, 1.0);
	glRotatef(rthigh_angle[1], 0.0, 1.0, 0.0);
	glRotatef(rthigh_angle[0], 1.0, 0.0, 0.0);
	glTranslatef(0.0, rthigh_scale[1] / -2.0, 0.0);
	glScalef(rthigh_scale[0], rthigh_scale[1], rthigh_scale[2]);
	draw_cube();
	glPopMatrix();

	GLfloat * right_knee_joint = calculate_joint_location(0.0, -rthigh_scale[1], rthigh_scale[2] / -2.0,
		                                                  rthigh_angle[0], rthigh_angle[1], rthigh_angle[2],
		                                                  joints.right_hip[0], joints.right_hip[1], joints.right_hip[2]);

	joints.right_knee[0] = right_knee_joint[0], joints.right_knee[1] = right_knee_joint[1], joints.right_knee[2] = right_knee_joint[2];

	GLfloat * delta = joints.right_hip;
	delta[1] += rthigh_scale[1] / -2.0;

	calculate_bounds(rthigh_scale, rthigh_angle, delta);
}

void draw_right_calf(int pants_color, int shoe_color)
{
	GLfloat * rcalf_scale = people[selected_person].body_parts[RIGHT_CALF].scale;
	GLfloat * rcalf_angle = people[selected_person].body_parts[RIGHT_CALF].angle;

	glPushMatrix();
	change_color(pants_color);
	glTranslatef(joints.right_knee[0], joints.right_knee[1], joints.right_knee[2]);
	glRotatef(rcalf_angle[2] + people[selected_person].body_parts[RIGHT_THIGH].angle[2], 0.0, 0.0, 1.0);
	glRotatef(rcalf_angle[1] + people[selected_person].body_parts[RIGHT_THIGH].angle[1], 0.0, 1.0, 0.0);
	glRotatef(rcalf_angle[0] + people[selected_person].body_parts[RIGHT_THIGH].angle[0], 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, rcalf_scale[1] / -2.0, rcalf_scale[2] / 2.0);
	glScalef(rcalf_scale[0], rcalf_scale[1], rcalf_scale[2]);
	draw_cube();
	glPopMatrix();
	draw_right_foot(shoe_color);
	glPopMatrix();

	GLfloat * delta = joints.right_knee;
	delta[1] += rcalf_scale[1] / -2.0;
	delta[2] += rcalf_scale[2] / 2.0;

	calculate_bounds(rcalf_scale, rcalf_angle, delta);
}

void draw_right_leg(int pants_color, int shoe_color)
{
	draw_right_thigh(pants_color);
	draw_right_calf(pants_color, shoe_color);
}

void draw_backpack(void)
{
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
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

void create_student(int num_args, ...)
{
	Person student = { 1, 0, 1.0, 2.0, { -100.0, 18.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, 0.1, { 0.0, 180.0, 0.0 } };
	char * skin_color, * shirt_color, * pants_color, * shoe_color;

	student.colors[0] = COLOR_SKIN;
	student.colors[1] = COLOR_GREEN;
	student.colors[2] = COLOR_BLUE;
	student.colors[3] = COLOR_BROWN;

	va_list arguments;
	va_start(arguments, num_args);
	if (num_people < MAX_PEOPLE)
	{
		switch (num_args)
		{
		case 1:
			skin_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], skin_color) == 0)
				{
					student.colors[0] = i;
					break;
				}
			break;
		case 2:
			skin_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], skin_color) == 0)
				{
					student.colors[0] = i;
					break;
				}

			shirt_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], shirt_color) == 0)
				{
					student.colors[1] = i;
					break;
				}
			break;
		case 3:
			skin_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], skin_color) == 0)
				{
					student.colors[0] = i;
					break;
				}

			shirt_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], shirt_color) == 0)
				{
					student.colors[1] = i;
					break;
				}

			pants_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], pants_color) == 0)
				{
					student.colors[2] = i;
					break;
				}
			break;
		case 4:
			skin_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], skin_color) == 0)
				{
					student.colors[0] = i;
					break;
				}

			shirt_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], shirt_color) == 0)
				{
					student.colors[1] = i;
					break;
				}

			pants_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], pants_color) == 0)
				{
					student.colors[2] = i;
					break;
				}

			shoe_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], shoe_color) == 0)
				{
					student.colors[3] = i;
					break;
				}
			break;
		default:
			break;
		}
		va_end(arguments);

		initialize_person(&student);
		people[num_people++] = student;
	}
}

void create_bystander(int num_args, ...)
{
	if (num_people < MAX_PEOPLE)
	{
		Person bystander = { 0, 0, 1.0, 2.0,{ -100.0, 18.0, 0.0, 1.0 },{ 0.0, 0.0, 0.0, 1.0 }, 0.1,{ 0.0, 180.0, 0.0 } };
		char * skin_color, * shirt_color, * pants_color, * shoe_color;

		bystander.colors[0] = COLOR_SKIN;
		bystander.colors[1] = COLOR_GRAY;
		bystander.colors[2] = COLOR_BLUE;
		bystander.colors[3] = COLOR_BLACK;

		va_list arguments;
		va_start(arguments, num_args);
		
		switch (num_args)
		{
		case 1:
			skin_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], skin_color) == 0)
				{
					bystander.colors[0] = i;
					break;
				}
			break;
		case 2:
			skin_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], skin_color) == 0)
				{
					bystander.colors[0] = i;
					break;
				}

			shirt_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], shirt_color) == 0)
				{
					bystander.colors[1] = i;
					break;
				}
			break;
		case 3:
			skin_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], skin_color) == 0)
				{
					bystander.colors[0] = i;
					break;
				}
			
			shirt_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], shirt_color) == 0)
				{
					bystander.colors[1] = i;
					break;
				}
			
			pants_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], pants_color) == 0)
				{
					bystander.colors[2] = i;
					break;
				}
			break;
		case 4:
			skin_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], skin_color) == 0)
				{
					bystander.colors[0] = i;
					break;
				}
			
			shirt_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], shirt_color) == 0)
				{
					bystander.colors[1] = i;
					break;
				}
			
			pants_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], pants_color) == 0)
				{
					bystander.colors[2] = i;
					break;
				}
			
			shoe_color = va_arg(arguments, char *);
			for (int i = 0; i < NUM_COLORS; i++)
				if (_stricmp(color_text[i], shoe_color) == 0)
				{
					bystander.colors[3] = i;
					break;
				}
			break;
		default:
			break;
		}
		va_end(arguments);

		initialize_person(&bystander);
		people[num_people++] = bystander;
	}
}

void select_person(int person)
{
	if (person < 0 || person > num_people)
	{
		print_command("Invalid person selected!");
	}
	else
	{
		selected_person = person;
		set_camera_position(3, people[person].position[0], people[person].position[1] + 10, people[person].position[2]);
		set_camera_target(3, people[person].position[0], 0, people[person].position[2]);
		set_camera_angle(2, 0.0, -90.0);
	}
}

void remove_person(int person)
{
	if (person < 0 || person > num_people)
	{
		print_command("Invalid person selected!");
	}
	else
	{
		for (int i = person; i < num_people; i++)
		{
			people[i] = people[i + 1];
		}
		if (person == selected_person) selected_person = 0;
		num_people--;
	}
}

void draw_person(int person)
{
	if (person < 0 || person > num_people)
	{
		print_command("Invalid person selected!");
	}
	else
	{
		people[person].bounds[0] = people[person].position[0];
		people[person].bounds[1] = 0.0;
		people[person].bounds[2] = people[person].position[2];
		people[person].bounds[3] = 0.0;
		people[person].bounds[4] = people[person].position[1];
		people[person].bounds[5] = 0.0;

		glTranslatef(people[person].position[0], people[person].position[1] * people[person].scale, people[person].position[2]);
		glScalef(people[person].scale, people[person].scale, people[person].scale);
		glPushMatrix();
		glRotatef(people[person].angle[2], 0.0, 0.0, 1.0);
		glRotatef(people[person].angle[1], 0.0, 1.0, 0.0);
		glRotatef(people[person].angle[0], 1.0, 0.0, 0.0);

		draw_body(people[person].colors[1]);
		draw_head(people[person].colors[0], person);
		draw_left_arm(people[person].colors[1], people[person].colors[0]);
		draw_right_arm(people[person].colors[1], people[person].colors[0]);
		draw_left_leg(people[person].colors[2], people[person].colors[3]);
		draw_right_leg(people[person].colors[2], people[person].colors[3]);
		if (people[person].is_student) draw_backpack();
		glPopMatrix();

		if (bounds_enabled()) draw_bounds();
		if (person == get_selected_person())
		{
			glPushMatrix();
			glTranslatef(0.0, 17.0, 0.0);
			glScalef(2.0, 2.0, 2.0);
			draw_diamond();
			glPopMatrix();
		}
	}
}

void rotate_person(GLfloat phi, GLfloat psi)
{
	people[selected_person].angle[0] = (int)(people[selected_person].angle[0] + phi) % 360;
	people[selected_person].angle[1] = (int)(people[selected_person].angle[1] + psi) % 360;
}

void translate_person(int person, GLfloat delta)
{
	people[person].position[0] += delta * people[person].scale * sin(people[person].angle[1] * (M_PI / 180));
	people[person].bounds[0] = people[person].position[0];
	people[person].position[2] += delta * people[person].scale * cos(people[person].angle[1] * (M_PI / 180));
	people[person].bounds[2] = people[person].position[2];
}

void scale_person(GLfloat factor)
{
	people[selected_person].scale = 0.1 * factor;
}

void jump(int person)
{
	if (person < 0 || person > num_people)
	{
		print_command("ERROR: Invalid person selected!");
	}
	else
	{
		people[person].in_air = 1;
		people[person].velocity[1] = 15.0;
	}
}

void rotate_head(GLfloat phi, GLfloat psi)
{
	GLfloat * head_angle = people[selected_person].body_parts[HEAD].angle;
	if (abs((int)(head_angle[0] + phi) % 360) < 45)
		head_angle[0] = (int)(head_angle[0] + phi) % 360;
	if (abs((int)(head_angle[1] + psi) % 360) < 90)
		head_angle[1] = (int)(head_angle[1] + psi) % 360;
}

void set_person_position(int person, int num_args, ...)
{
	if (person < 0 || person > num_people)
	{
		print_command("ERROR: Invalid person selected!");
	}
	else
	{
		va_list arguments;
		va_start(arguments, num_args);

		switch (num_args)
		{
		case 1:
			people[person].position[0] = va_arg(arguments, double);
			break;
		case 2:
			people[person].position[0] = va_arg(arguments, double);
			people[person].position[1] = va_arg(arguments, double);
			break;
		case 3:
			people[person].position[0] = va_arg(arguments, double);
			people[person].position[1] = va_arg(arguments, double);
			people[person].position[2] = va_arg(arguments, double);
			break;
		default:
			break;
		}

		va_end(arguments);

		char str[100];
		sprintf_s(str, 50, "Set position of person %i to %.1f, %.1f, %.1f", person, people[person].position[0], people[person].position[1], people[person].position[2]);
		print_command(str);
	}
}

void set_person_scale(int person, GLfloat scale)
{
	if (person < 0 || person > num_people)
	{
		print_command("ERROR: Invalid person selected!");
	}
	else if (scale < 0)
	{
		print_command("ERROR: Scale can't be smaller than 0!");
	}
	else
	{
		people[person].scale = scale;

		char str[100];
		sprintf_s(str, 50, "Set scale of person %i to %.1f", person, people[person].scale);
		print_command(str);
	}
}

void set_person_angle(int suppress_msg, int person, int num_args, ...)
{
	
	if (person < 0 || person > num_people)
	{
		print_command("ERROR: Invalid person selected!");
	}
	else
	{
		va_list arguments;
		va_start(arguments, num_args);

		switch (num_args)
		{
		case 1:
			people[person].angle[0] = va_arg(arguments, double);
			break;
		case 2:
			people[person].angle[0] = va_arg(arguments, double);
			people[person].angle[1] = va_arg(arguments, double);
			break;
		case 3:
			people[person].angle[0] = va_arg(arguments, double);
			people[person].angle[1] = va_arg(arguments, double);
			people[person].angle[2] = va_arg(arguments, double);
			break;
		default:
			break;
		}

		va_end(arguments);

		if (!suppress_msg)
		{
			char str[100];
			sprintf_s(str, 50, "Set angle of person %i to %.1f, %.1f, %.1f", person, people[person].angle[0], people[person].angle[1], people[person].angle[2]);
			print_command(str);
		}
	}
}

void rotate_body_part_angle(int person, char * body_part, int num_args, ...)
{
	if (person < 0 || person > num_people)
	{
		print_command("ERROR: Invalid person selected!");
	}
	else
	{
		va_list arguments;
		va_start(arguments, num_args);

		for (int i = 0; i < NUM_BODY_PARTS; i++)
		{
			if (_stricmp(body_part, str_parts[i]) == 0)
			{
				switch (num_args)
				{
				case 1:
					people[person].body_parts[i].angle[0] += va_arg(arguments, double);
					break;
				case 2:
					people[person].body_parts[i].angle[0] += va_arg(arguments, double);
					people[person].body_parts[i].angle[1] += va_arg(arguments, double);
					break;
				case 3:
					people[person].body_parts[i].angle[0] += va_arg(arguments, double);
					people[person].body_parts[i].angle[1] += va_arg(arguments, double);
					people[person].body_parts[i].angle[2] += va_arg(arguments, double);
					break;
				default:
					break;
				}
				va_end(arguments);

				char str[100];
				sprintf_s(str, 50, "Set %s angle of person %i to %.1f, %.1f, %.1f", body_part, person, people[person].body_parts[i].angle[0], 
																									   people[person].body_parts[i].angle[1], 
																									   people[person].body_parts[i].angle[2]);
				print_command(str);
				return;
			}
		}
		print_command("ERROR: Invalid body part selected!");
	}
}

GLfloat * get_position(void)
{
	return people[selected_person].position;
}

GLfloat * get_bounds(void)
{
	return people[selected_person].bounds;
}

int get_selected_person(void)
{
	return selected_person;
}

Person * get_people(void)
{
	return people;
}

Person get_person(int person)
{
	if (person < 0 || person > num_people)
	{
		print_command("Invalid person selected!");
		return people[selected_person];
	}
	else
	{
		return people[person];
	}
}

int get_num_people(void)
{
	return num_people;
}

void reset_person(void)
{
	for (int i = 0; i < 3; i++) people[selected_person].position[i] = initial_pos[i];
	for (int i = 0; i < 3; i++) people[selected_person].velocity[i] = 0.0;
	for (int i = 0; i < 3; i++) people[selected_person].angle[i] = initial_angle[i];
	for (int i = 0; i < 11; i++)
		for (int j = 0; j < 3; j++) 
			people[selected_person].body_parts[i].angle[j] = 0.0;
	people[selected_person].scale = initial_scale;
}

GLfloat * calculate_joint_location(GLfloat point1_x, GLfloat point1_y, GLfloat point1_z, 
							  GLfloat phi, GLfloat psi, GLfloat theta,
							  GLfloat point2_x, GLfloat point2_y, GLfloat point2_z)
{
	GLfloat joint_x = point1_x * (cos(psi * M_PI / 180) * cos(theta * M_PI / 180)) +
		              point1_y * (-cos(psi * M_PI / 180) * sin(theta * M_PI / 180)) +
					  point1_z * (sin(psi* M_PI / 180));

	GLfloat joint_y = point1_x * (sin(phi * M_PI / 180) * sin(psi * M_PI / 180) * cos(theta * M_PI / 180) + cos(phi * M_PI / 180) * sin(theta * M_PI / 180)) +
		              point1_y * (-sin(phi * M_PI / 180) * sin(psi * M_PI / 180) * sin(theta * M_PI / 180) + cos(phi * M_PI / 180) * cos(theta * M_PI / 180)) +
		              point1_z * (-sin(phi * M_PI / 180) * cos(psi * M_PI / 180));

	GLfloat joint_z = point1_x * (-cos(phi * M_PI / 180) * sin(psi * M_PI / 180) * cos(theta * M_PI / 180) + sin(phi * M_PI / 180) * sin(theta * M_PI / 180)) +
		              point1_y * (cos(phi * M_PI / 180) * sin(psi * M_PI / 180) * sin(theta * M_PI / 180) + sin(phi * M_PI / 180) * cos(theta * M_PI / 180)) +
		              point1_z * (cos(phi * M_PI / 180) * cos(psi * M_PI / 180));

	GLfloat joint_location[3] = { joint_x + point2_x, joint_y + point2_y, joint_z + point2_z };

	return joint_location;
}

static void calculate_bounds(GLfloat * scale, GLfloat * angle, GLfloat * delta)
{
	GLfloat points[8][3] = { { -scale[0] / 2, -scale[1] / 2, scale[2] / 2 }, { scale[0] / 2, -scale[1] / 2, scale[2] / 2 },
							 { scale[0] / 2, scale[1] / 2, scale[2] / 2 }, { -scale[0] / 2, scale[1] / 2, scale[2] / 2 },
							 { scale[0] / 2, -scale[1] / 2, -scale[2] / 2 }, { -scale[0] / 2, -scale[1] / 2, -scale[2] / 2 },
							 { -scale[0] / 2, scale[1] / 2, -scale[2] / 2 }, { scale[0] / 2, scale[1] / 2, -scale[2] / 2 } };

	for (int i = 0; i < 8; i++)
	{
		GLfloat point_x = (points[i][0] * (cos(angle[1] * M_PI / 180) * cos(angle[2] * M_PI / 180)) +
						  points[i][1] * (-cos(angle[1] * M_PI / 180) * sin(angle[2] * M_PI / 180)) +
						  points[i][2] * (sin(angle[1] * M_PI / 180)) + delta[0]) * people[selected_person].scale;

		if (fabs(point_x) > people[selected_person].bounds[1])
		{
			people[selected_person].bounds[1] = fabs(point_x);
		}

		GLfloat point_y = (points[i][0] * (sin(angle[0] * M_PI / 180) * cos(angle[1] * M_PI / 180) * cos(angle[2] * M_PI / 180) + cos(angle[0] * M_PI / 180) * sin(angle[2] * M_PI / 180)) +
						  points[i][1] * (-sin(angle[0] * M_PI / 180) * sin(angle[1] * M_PI / 180) * sin(angle[2] * M_PI / 180) + cos(angle[0] * M_PI / 180) * cos(angle[2] * M_PI / 180)) +
						  points[i][2] * (-sin(angle[0] * M_PI / 180) * cos(angle[1] * M_PI / 180)) + delta[1]) * people[selected_person].scale;

		if (fabs(point_y) > people[selected_person].bounds[5])
		{
			people[selected_person].bounds[5] = fabs(point_y);
		}

		GLfloat point_z = (points[i][0] * (-cos(angle[0] * M_PI / 180) * sin(angle[1] * M_PI / 180) * cos(angle[2] * M_PI / 180) + sin(angle[0] * M_PI / 180) * sin(angle[2] * M_PI / 180)) +
						  points[i][1] * (cos(angle[0] * M_PI / 180) * sin(angle[1] * M_PI / 180) * sin(angle[2] * M_PI / 180) + sin(angle[0] * M_PI / 180) * cos(angle[2] * M_PI / 180)) +
						  points[i][2] * (cos(angle[0] * M_PI / 180) * cos(angle[1] * M_PI / 180)) + delta[2]) * people[selected_person].scale;

		if (fabs(point_z) > people[selected_person].bounds[3])
		{
			people[selected_person].bounds[3] = fabs(point_z);
		}
	}
}

static void draw_bounds(void)
{
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(1.0);

	GLfloat x = people[selected_person].bounds[1] / people[selected_person].scale;
	GLfloat neg_x = -x;
	GLfloat y = people[selected_person].bounds[5] / people[selected_person].scale;
	GLfloat neg_y = -y;
	GLfloat z = people[selected_person].bounds[3] / people[selected_person].scale;
	GLfloat neg_z = -z;

	glBegin(GL_LINE_LOOP);
		glVertex3f(neg_x, neg_y, z);
		glVertex3f(x, neg_y, z);
		glVertex3f(x, y, z);
		glVertex3f(neg_x, y, z);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex3f(x, neg_y, z);
		glVertex3f(x, neg_y, neg_z);
		glVertex3f(x, y, neg_z);
		glVertex3f(x, y, z);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex3f(x, neg_y, neg_z);
		glVertex3f(neg_x, neg_y, neg_z);
		glVertex3f(neg_x, y, neg_z);
		glVertex3f(x, y, neg_z);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex3f(neg_x, neg_y, neg_z);
		glVertex3f(neg_x, neg_y, z);
		glVertex3f(neg_x, y, z);
		glVertex3f(neg_x, y, neg_z);
	glEnd();

	glPopMatrix();
}

static void list_people(void)
{
	char str[100] = "List of people:";
	print_command("");
	print_command(str);

	for (int i = 0; i < num_people; i++)
	{
		sprintf_s(str, 100, "Person %d : ", i);
		if (people[i].is_student)
			strcat_s(str, 100, "STUDENT");
		else
			strcat_s(str, 100, "BYSTANDER");

		print_command(str);
	}
}

void person_commands(int num_args, char * args[])
{
	if (num_args > 0)
	{
		if (_stricmp(args[1], "list") == 0)
		{
			list_people();
		}
		else if (_stricmp(args[1], "create") == 0)
		{
			if (num_args >= 2)
			{
				if (_stricmp(args[2], "student") == 0)
				{
					if (num_args == 2) create_student(0);
					else if (num_args == 3) create_student(1, args[3]);
					else if (num_args == 4) create_student(2, args[3], args[4]);
					else if (num_args == 5) create_student(3, args[3], args[4], args[5]);
					else if (num_args == 6) create_student(4, args[3], args[4], args[5], args[6]);
					else
					{
						print_command("");
						print_command("Usage: Creates a new student with the specified colors");
						print_command("Colors: skin red brown green blue gray white orange black grass");
						print_command("\"/person create student [skin_color shirt_color pants_color shoe_color]\"");
					}
				}
				else if (_stricmp(args[2], "bystander") == 0)
				{
					if (num_args == 2) create_bystander(0);
					else if (num_args == 3) create_bystander(1, args[3]);
					else if (num_args == 4) create_bystander(2, args[3], args[4]);
					else if (num_args == 5) create_bystander(3, args[3], args[4], args[5]);
					else if (num_args == 6) create_bystander(4, args[3], args[4], args[5], args[6]);
					else
					{
						print_command("");
						print_command("Usage: Creates a new bystander with the specified colors");
						print_command("Colors: skin red brown green blue gray white orange black grass");
						print_command("\"/person create bystander skin_color shirt_color pants_color shoe_color\"");
					}
				}
				else
				{
					print_command("");
					print_command("Usage: Creates a new student or bystander");
					print_command("\"/person create [student | bystander]\"");
				}
			}
			else
			{
				print_command("");
				print_command("Usage: Creates a new student or bystander");
				print_command("\"/person create [student | bystander]\"");
			}
		}
		else if (_stricmp(args[1], "select") == 0)
		{
			if (num_args == 2) select_person(atoi(args[2]));
			else
			{
				print_command("");
				print_command("Usage: Selects a person");
				print_command("\"/person select <person>\"");
			}
		}
		else if (_stricmp(args[1], "set") == 0)
		{
			if (num_args >= 2)
			{
				if (_stricmp(args[2], "position") == 0)
				{
					if (num_args == 4) set_person_position(atoi(args[3]), 1, atof(args[4]));
					else if (num_args == 5) set_person_position(atoi(args[3]), 2, atof(args[4]), atof(args[5]));
					else if (num_args == 6) set_person_position(atoi(args[3]), 3, atof(args[4]), atof(args[5]), atof(args[6]));
					else
					{
						print_command("");
						print_command("Usage: Sets the position of the specified person");
						print_command("\"/person set position <person> <x> [y z]\"");
					}
				}
				else if (_stricmp(args[2], "angle") == 0)
				{
					if (num_args == 4) set_person_angle(0, atoi(args[3]), 1, atof(args[4]));
					else if (num_args == 5) set_person_angle(0, atoi(args[3]), 2, atof(args[4]), atof(args[5]));
					else if (num_args == 6) set_person_angle(0, atoi(args[3]), 3, atof(args[4]), atof(args[5]), atof(args[6]));
					else
					{
						print_command("");
						print_command("Usage: Sets the angle of rotation for the specified person");
						print_command("\"/person set angle <person> <x> [y z]\"");
					}
				}
				else if (_stricmp(args[2], "body_part_angle") == 0)
				{
					if (num_args == 5) rotate_body_part_angle(atoi(args[3]), args[4], 1, atof(args[5]));
					else if (num_args == 6) rotate_body_part_angle(atoi(args[3]), args[4], 2, atof(args[5]), atof(args[6]));
					else if (num_args == 7) rotate_body_part_angle(atoi(args[3]), args[4], 3, atof(args[5]), atof(args[6]), atof(args[7]));
					else
					{
						print_command("");
						print_command("Usage: Sets the angle of the specified body part of the specified person");
						print_command("Body Parts: HEAD NECK BODY LEFT_BICEP LEFT_FOREARM");
						print_command("            RIGHT_BICEP RIGHT_FOREARM LEFT_THIGH LEFT_CALF RIGHT_THIGH RIGHT_CALF");
						print_command("\"/person set body_part_angle <person> <BODY_PART> <x> [y z]\"");
					}
				}
				else if (_stricmp(args[2], "scale") == 0)
				{
					if (num_args == 4) set_person_scale(atoi(args[3]), atof(args[4]));
					else
					{
						print_command("");
						print_command("Usage: Sets the scale of the specified person");
						print_command("\"/person set scale <person> <factor>\"");
					}
				}
				else
				{
					print_command("");
					print_command("Usage: Sets an attribute of the specified person");
					print_command("\"/person set [position | angle | body_part_angle | scale]\"");
				}
			}
			else
			{
				print_command("");
				print_command("Usage: Sets an attribute of the specified person");
				print_command("\"/person set [position | angle | body_part_angle | scale]\"");
			}
		}
		else if (_stricmp(args[1], "jump") == 0)
		{
			if (num_args == 2)
			{
				jump(atoi(args[2]));
			}
			else
			{
				print_command("");
				print_command("Usage: Makes a person jump");
				print_command("\"/person jump <person>\"");
			}
		}
		else if (_stricmp(args[1], "remove") == 0)
		{
			if (num_args == 2)
			{
				remove_person(atoi(args[2]));
			}
			else
			{
				print_command("");
				print_command("Usage: Removes a person");
				print_command("\"/person remove <person>\"");
			}
		}
		else
		{
			char * sub_commands = get_sub_commands("person");
			char str[100] = "/person ";
			int str_length = strlen(str);

			print_command("");
			print_command("List of person commands:");
			for (int i = 0; i < get_num_sub_commands(args[0]); i++)
			{
				memcpy(str + str_length, sub_commands + (i * 20), 20);
				print_command(str);
			}
		}
	}
	else
	{
		char * sub_commands = get_sub_commands("person");
		char str[100] = "/person ";
		int str_length = strlen(str);

		print_command("");
		print_command("List of person commands:");
		for (int i = 0; i < get_num_sub_commands(args[0]); i++)
		{
			memcpy(str + str_length, sub_commands + (i * 20), 20);
			print_command(str);
		}
	}
}