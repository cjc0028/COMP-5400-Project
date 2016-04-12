/*
* Name: Chase Counsell
* Project: COMP 5400 Project 4
* File: student.c
* Date: 3/1/2016
* Description: Functions for drawing individual parts of the 3D student
*/
#define MAX_BYSTANDERS 10
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdlib.h>
#include<GL\glut.h>
#include "student.h"
#include "cube.h"

GLfloat * calculate_joint_location(GLfloat point1_x, GLfloat point1_y, GLfloat point1_z,
								   GLfloat phi, GLfloat psi, GLfloat theta,
								   GLfloat point2_x, GLfloat point2_y, GLfloat point2_z);

enum parts {HEAD, NECK, BODY, LEFT_BICEP, LEFT_FOREARM, RIGHT_BICEP, RIGHT_FOREARM, LEFT_THIGH, LEFT_CALF, RIGHT_THIGH, RIGHT_CALF};

typedef struct
{
	GLfloat scale[3];
	GLfloat angle[3];
}Body_Part;

Body_Part body_part_list[11];

typedef struct
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

typedef struct
{
	GLfloat position[3];                                               // X, Y, and Z position
	GLfloat scale;                                                     // Scale used in all directions
	GLfloat angle[3];                                                  // [0] - body tilt, [1] - body rotation
	GLfloat head_angle[3];
} Person;

Person student = { { -100.0, 1.9, 0.0 }, 1.0,{ 0.0, 180.0, 0.0 },{ 0.0, 0.0, 0.0 } };
Person bystanders[MAX_BYSTANDERS];

int bystander_colors[4] = { -1, -1, -1, -1 };


Body_Part neck = { { 0.0, 0.0, 0.0 } };
void draw_neck(int skin_color)
{
	neck.scale[0] = 4.0, neck.scale[1] = 0.5, neck.scale[2] = 4.0;

	glPushMatrix();
	change_color(skin_color);
	glTranslatef(joints.neck_to_body[0], joints.neck_to_body[1], joints.neck_to_body[2]);
	glTranslatef(0.0, neck.scale[1] / 2.0, 0.0);
	glScalef(neck.scale[0], neck.scale[1], neck.scale[2]);
	draw_cube();
	glPopMatrix();

	body_part_list[NECK] = neck;

	GLfloat * delta = calculate_joint_location(0.0, neck.scale[1], 0.0,
											   neck.angle[0], neck.angle[1], neck.angle[2],
											   joints.neck_to_body[0], joints.neck_to_body[1], joints.neck_to_body[2]);

	joints.head_to_neck[0] = delta[0];
	joints.head_to_neck[1] = delta[1];
	joints.head_to_neck[2] = delta[2];
}

void draw_hair(void)
{
	glPushMatrix();
	glColor3f(0.37, 0.15, 0.02);
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
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-1.5, 4.1, 4.01);
	glScalef(2.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(-1.3, 4.0, 4.02);
	glScalef(0.75, 0.75, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(1.5, 4.1, 4.01);
	glScalef(2.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(1.3, 4.0, 4.02);
	glScalef(0.75, 0.75, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.0, 2.0, 4.01);
	glBegin(GL_POLYGON);
		glVertex2f(-2.0, 0.25);
		glVertex2f(-2.0, -0.25);
		glVertex2f(2.0, -0.25);
		glVertex2f(2.0, 0.25);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}

Body_Part head = { { 0.0, 0.0, 0.0 } };
void draw_head(int skin_color)
{
	head.scale[0] = 8.0, head.scale[1] = 8.0, head.scale[2] = 8.0;

	draw_neck(skin_color);
	
	glPushMatrix();
	glTranslatef(joints.head_to_neck[0], joints.head_to_neck[1], joints.head_to_neck[2]);
	glRotatef(head.angle[1] = student.head_angle[1], 0.0, 1.0, 0.0);
	glRotatef(head.angle[0] = student.head_angle[0], 1.0, 0.0, 0.0);

	glPushMatrix();
	change_color(skin_color);
	glTranslatef(0.0, head.scale[1] / 2.0, 0.0);
	glScalef(head.scale[0], head.scale[1], head.scale[2]);
	draw_cube();
	glPopMatrix();

	draw_hair();
	draw_face();
	glPopMatrix();

	body_part_list[HEAD] = head;
}

Body_Part body = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 } };
void draw_body(int shirt_color)
{
	body.scale[0] = 8.0, body.scale[1] = 12.0, body.scale[2] = 4.0;

	glPushMatrix();
	change_color(shirt_color);
	glScalef(body.scale[0], body.scale[1], body.scale[2]);
	draw_cube();
	glPopMatrix();

	body_part_list[BODY] = body;

	GLfloat * neck_body_joint = calculate_joint_location(0.0, body.scale[1] / 2.0, 0.0, 
												         body.angle[0], body.angle[1], body.angle[2],
												         0.0, 0.0, 0.0);

	joints.neck_to_body[0] = neck_body_joint[0], joints.neck_to_body[1] = neck_body_joint[1], joints.neck_to_body[2] = neck_body_joint[2];

	GLfloat * left_shoulder_joint = calculate_joint_location(body.scale[0] / 2.0, body.scale[1] / 2.0, 0.0,
		                                                     body.angle[0], body.angle[1], body.angle[2], 
		                                                     0.0, 0.0, 0.0);

	joints.left_shoulder[0] = left_shoulder_joint[0], joints.left_shoulder[1] = left_shoulder_joint[1], joints.left_shoulder[2] = left_shoulder_joint[2];
	
	GLfloat * right_shoulder_joint = calculate_joint_location(body.scale[0] / -2.0, body.scale[1] / 2.0, 0.0,
		                                                      body.angle[0], body.angle[1], body.angle[2],
		                                                      0.0, 0.0, 0.0);

	joints.right_shoulder[0] = right_shoulder_joint[0], joints.right_shoulder[1] = right_shoulder_joint[1], joints.right_shoulder[2] = right_shoulder_joint[2];
	
	GLfloat * left_hip_joint = calculate_joint_location(body.scale[0] / 4.0, body.scale[1] / -2.0, 0.0,
		                                                body.angle[0], body.angle[1], body.angle[2],
		                                                0.0, 0.0, 0.0);

	joints.left_hip[0] = left_hip_joint[0], joints.left_hip[1] = left_hip_joint[1], joints.left_hip[2] = left_hip_joint[2];
	
	GLfloat * right_hip_joint = calculate_joint_location(body.scale[0] / -4.0, body.scale[1] / -2.0, 0.0,
		                                                 body.angle[0], body.angle[1], body.angle[2],
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

Body_Part left_bicep = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 } };
void draw_left_bicep(int shirt_color)
{
	left_bicep.scale[0] = 4.0, left_bicep.scale[1] = 5.0, left_bicep.scale[2] = 4.0;

	glPushMatrix();
	change_color(shirt_color);
	glTranslatef(joints.left_shoulder[0], joints.left_shoulder[1], joints.left_shoulder[2]);
	glRotatef(left_bicep.angle[2] = 45, 0.0, 0.0, 1.0);
	glTranslatef(left_bicep.scale[0] / 2.0, left_bicep.scale[1] / -2.0, 0.0);
	glScalef(left_bicep.scale[0], left_bicep.scale[1], left_bicep.scale[2]);
	draw_cube();
	glPopMatrix();

	body_part_list[LEFT_BICEP] = left_bicep;

	GLfloat * left_elbow_joint = calculate_joint_location(left_bicep.scale[0] / 2.0, -left_bicep.scale[1], left_bicep.scale[2] / 2.0, 
		                                                  left_bicep.angle[0], left_bicep.angle[1], left_bicep.angle[2],
		                                                  joints.left_shoulder[0], joints.left_shoulder[1], joints.left_shoulder[2]);

	joints.left_elbow[0] = left_elbow_joint[0], joints.left_elbow[1] = left_elbow_joint[1], joints.left_elbow[2] = left_elbow_joint[2];
}

Body_Part left_forearm = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 } };
void draw_left_forearm(int shirt_color, int skin_color)
{
	left_forearm.scale[0] = 4.0, left_forearm.scale[1] = 5.0, left_forearm.scale[2] = 4.0;

	glPushMatrix();
	change_color(shirt_color);
	glTranslatef(joints.left_elbow[0], joints.left_elbow[1], joints.left_elbow[2]);
	glRotatef(left_forearm.angle[2] = left_bicep.angle[2], 0.0, 0.0, 1.0);
	glRotatef(left_forearm.angle[0] = -15, 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, -2.5, -2.0);
	glScalef(left_forearm.scale[0], left_forearm.scale[1], left_forearm.scale[2]);
	draw_cube();
	glPopMatrix();
	draw_left_hand(skin_color);
	glPopMatrix();

	body_part_list[LEFT_FOREARM] = left_forearm;
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
	glPushMatrix();
	glTranslatef(0.0, -8.8, -2.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(3.5, 6.0, 1.0);
	draw_cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.2, -8.8, -0.99);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(3.0, 5.0, 1.0);
	change_color(COLOR_WHITE);
	cube_face(0, 1, 2, 3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.2, -9.8, -0.98);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	change_color(COLOR_RED);
	cube_face(0, 1, 2, 3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.2, -8.8, -0.98);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	change_color(COLOR_BROWN);
	cube_face(0, 1, 2, 3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.2, -7.8, -0.98);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	change_color(COLOR_GRAY);
	cube_face(0, 1, 2, 3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.2, -9.8, -0.98);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	change_color(COLOR_BLUE);
	cube_face(0, 1, 2, 3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.2, -8.8, -0.98);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	change_color(COLOR_ORANGE);
	cube_face(0, 1, 2, 3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.2, -7.8, -0.98);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	change_color(COLOR_GREEN);
	cube_face(0, 1, 2, 3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.2, -9.8, -0.98);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	change_color(COLOR_BLUE);
	cube_face(0, 1, 2, 3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.8, -9.8, -0.98);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	change_color(COLOR_GRAY);
	cube_face(0, 1, 2, 3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.8, -8.8, -0.98);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	change_color(COLOR_GREEN);
	cube_face(0, 1, 2, 3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.8, -7.8, -0.98);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	change_color(COLOR_ORANGE);
	cube_face(0, 1, 2, 3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.65, -8.8, -0.98);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.5, 0.5, 1.0);
	change_color(COLOR_BLACK);
	cube_face(0, 1, 2, 3);
	glPopMatrix();

	glPopMatrix();
}

void draw_right_hand(int skin_color)
{
	glPushMatrix();
	change_color(skin_color);
	glTranslatef(0.0, -6.0, -2.0);
	glScalef(4.0, 2.0, 4.0);
	draw_cube();
	glPopMatrix();
}

Body_Part right_bicep = { { 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 } };
void draw_right_bicep(int shirt_color)
{
	right_bicep.scale[0] = 4.0, right_bicep.scale[1] = 5.0, right_bicep.scale[2] = 4.0;

	glPushMatrix();
	change_color(shirt_color);
	glTranslatef(joints.right_shoulder[0], joints.right_shoulder[1], joints.right_shoulder[2]);
	glRotatef(right_bicep.angle[2] = -15, 0.0, 0.0, 1.0);
	glTranslatef(right_bicep.scale[0] / -2.0, right_bicep.scale[1] / -2.0, 0.0);
	glScalef(right_bicep.scale[0], right_bicep.scale[1], right_bicep.scale[2]);
	draw_cube();
	glPopMatrix();

	body_part_list[RIGHT_BICEP] = right_bicep;

	GLfloat * right_elbow_joint = calculate_joint_location(right_bicep.scale[0] / -2.0, -right_bicep.scale[1], right_bicep.scale[2] / 2.0,
		                                                   right_bicep.angle[0], right_bicep.angle[1], right_bicep.angle[2],
		                                                   joints.right_shoulder[0], joints.right_shoulder[1], joints.right_shoulder[2]);

	joints.right_elbow[0] = right_elbow_joint[0], joints.right_elbow[1] = right_elbow_joint[1], joints.right_elbow[2] = right_elbow_joint[2];
}

Body_Part right_forearm = { { 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 } };
void draw_right_forearm(int shirt_color, int skin_color)
{
	right_forearm.scale[0] = 4.0, right_forearm.scale[1] = 5.0, right_forearm.scale[2] = 4.0;

	glPushMatrix();
	change_color(shirt_color);
	glTranslatef(joints.right_elbow[0], joints.right_elbow[1], joints.right_elbow[2]);
	glRotatef(right_forearm.angle[2] = right_bicep.angle[2], 0.0, 0.0, 1.0);
	glRotatef(right_forearm.angle[0] = -90, 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, -2.5, -2.0);
	glScalef(right_forearm.scale[0], right_forearm.scale[1], right_forearm.scale[2]);
	draw_cube();
	glPopMatrix();
	draw_right_hand(skin_color);
	draw_phone();
	glPopMatrix();

	body_part_list[RIGHT_FOREARM] = right_forearm;
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

Body_Part left_thigh = { { 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 } };
void draw_left_thigh(int pants_color)
{
	left_thigh.scale[0] = 4.0, left_thigh.scale[1] = 5.0, left_thigh.scale[2] = 4.0;

	glPushMatrix();
	change_color(pants_color);
	glTranslatef(joints.left_hip[0], joints.left_hip[1], joints.left_hip[2]);
	glRotatef(left_thigh.angle[0] = 0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, left_thigh.scale[1] / -2.0, 0.0);
	glScalef(left_thigh.scale[0], left_thigh.scale[1], left_thigh.scale[2]);
	draw_cube();
	glPopMatrix();

	body_part_list[LEFT_THIGH] = left_thigh;

	GLfloat * left_knee_joint = calculate_joint_location(0.0, -left_thigh.scale[1], left_thigh.scale[2] / -2.0,
		                                                 left_thigh.angle[0], left_thigh.angle[1], left_thigh.angle[2],
		                                                 joints.left_hip[0], joints.left_hip[1], joints.left_hip[2]);

	joints.left_knee[0] = left_knee_joint[0], joints.left_knee[1] = left_knee_joint[1], joints.left_knee[2] = left_knee_joint[2];
}

Body_Part left_calf = { { 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 } };
void draw_left_calf(int pants_color, int shoe_color)
{
	left_calf.scale[0] = 4.0, left_calf.scale[1] = 5.0, left_calf.scale[2] = 4.0;

	glPushMatrix();
	change_color(pants_color);
	glTranslatef(joints.left_knee[0], joints.left_knee[1], joints.left_knee[2]);
	glRotatef(left_calf.angle[0] = 0.0, 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, -2.5, 2.0);
	glScalef(left_calf.scale[0], left_calf.scale[1], left_calf.scale[2]);
	draw_cube();
	glPopMatrix();
	draw_left_foot(shoe_color);
	glPopMatrix();

	body_part_list[LEFT_CALF] = left_calf;
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

Body_Part right_thigh = { { 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 } };
void draw_right_thigh(int pants_color)
{
	right_thigh.scale[0] = 4.0, right_thigh.scale[1] = 5.0, right_thigh.scale[2] = 4.0;

	glPushMatrix();
	change_color(pants_color);
	glTranslatef(joints.right_hip[0], joints.right_hip[1], joints.right_hip[2]);
	glRotatef(right_thigh.angle[0] = 30, 1.0, 0.0, 0.0);
	glTranslatef(0.0, right_thigh.scale[1] / -2.0, 0.0);
	glScalef(right_thigh.scale[0], right_thigh.scale[1], right_thigh.scale[2]);
	draw_cube();
	glPopMatrix();

	body_part_list[RIGHT_THIGH] = right_thigh;

	GLfloat * right_knee_joint = calculate_joint_location(0.0, -right_thigh.scale[1], right_thigh.scale[2] / -2.0,
		                                                  right_thigh.angle[0], right_thigh.angle[1], right_thigh.angle[2],
		                                                  joints.right_hip[0], joints.right_hip[1], joints.right_hip[2]);

	joints.right_knee[0] = right_knee_joint[0], joints.right_knee[1] = right_knee_joint[1], joints.right_knee[2] = right_knee_joint[2];
}

Body_Part right_calf = { { 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 } };
void draw_right_calf(int pants_color, int shoe_color)
{
	right_calf.scale[0] = 4.0, right_calf.scale[1] = 5.0, right_calf.scale[2] = 4.0;

	glPushMatrix();
	change_color(pants_color);
	glTranslatef(joints.right_knee[0], joints.right_knee[1], joints.right_knee[2]);
	glRotatef(right_calf.angle[0] = 60.0, 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, right_calf.scale[1] / -2.0, right_calf.scale[2] / 2.0);
	glScalef(right_calf.scale[0], right_calf.scale[1], right_calf.scale[2]);
	draw_cube();
	glPopMatrix();
	draw_right_foot(shoe_color);
	glPopMatrix();

	body_part_list[RIGHT_CALF] = right_calf;
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

void draw_student(void)
{
	glTranslatef(student.position[0], student.position[1] * student.scale, student.position[2]);
	glScalef(student.scale, student.scale, student.scale);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(student.angle[1], 0.0, 1.0, 0.0);

	draw_body(COLOR_GREEN);
	draw_head(COLOR_SKIN);
	draw_left_arm(COLOR_GREEN, COLOR_SKIN);
	draw_right_arm(COLOR_GREEN, COLOR_SKIN);
	draw_left_leg(COLOR_BLUE, COLOR_BROWN);
	draw_right_leg(COLOR_BLUE, COLOR_BROWN);
	draw_backpack();
}

void draw_bystander(void)
{
	glTranslatef(-100.0, 1.9 * student.scale, 0.0);
	glScalef(student.scale, student.scale, student.scale);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(180, 0.0, 1.0, 0.0);

	for (int i = 0; i < 4; i++)
		if (bystander_colors[i] == -1) bystander_colors[i] = rand() % 7;

	draw_head(bystander_colors[0]);
	draw_body(bystander_colors[1]);
	draw_left_arm(bystander_colors[1], bystander_colors[0]);
	draw_right_arm(bystander_colors[1],bystander_colors[0]);
	draw_left_leg(bystander_colors[2], bystander_colors[3]);
	draw_right_leg(bystander_colors[2], bystander_colors[3]);
}

void rotate_student(GLfloat phi, GLfloat psi)
{
	student.angle[0] = (int)(student.angle[0] + phi) % 360;
	student.angle[1] = (int)(student.angle[1] + psi) % 360;
}

void translate_student(GLfloat delta)
{
	student.position[0] += delta * sin(student.angle[1] * (M_PI / 180));
	student.position[2] += delta * cos(student.angle[1] * (M_PI / 180));
}

void scale_student(GLfloat factor)
{
	student.scale = factor;
}

void rotate_head(GLfloat phi, GLfloat psi)
{
	if (abs((int)(student.head_angle[0] + phi) % 360) < 45)
		student.head_angle[0] = (int)(student.head_angle[0] + phi) % 360;
	if (abs((int)(student.head_angle[1] + psi) % 360) < 90)
		student.head_angle[1] = (int)(student.head_angle[1] + psi) % 360;
}

void reset_student(void)
{
	Person initial_student = { { -100.0, 1.9, 0.0 }, 1.0,{ 0.0, 180.0 },{ 0.0, 0.0 } };
	student = initial_student;
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