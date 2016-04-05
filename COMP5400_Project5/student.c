/*
* Name: Chase Counsell
* Project: COMP 5400 Project 4
* File: student.c
* Date: 3/1/2016
* Description: Functions for drawing individual parts of the 3D student
*/

#define _USE_MATH_DEFINES
#include<math.h>
#include<GL\glut.h>
#include "student.h"
#include "cube.h"

struct Student
{
	GLfloat position[3];                                               // X, Y, and Z position
	GLfloat scale;                                                     // Scale used in all directions
	GLfloat angle[2];                                                  // [0] - body tilt, [1] - body rotation
	GLfloat head_angle[2];
};

struct Student student1 = { {0.0, 1.9, 0.0}, 1.0, {0.0, 180.0}, {0.0, 0.0} };
struct Student initial_student = { { 0.0, 1.9, 0.0 }, 1.0,{ 0.0, 180.0 },{ 0.0, 0.0 } };

void draw_head(void)
{
	glPushMatrix();
	glTranslatef(0.0, 6.5, 0.0);
	glRotatef(student1.head_angle[1], 0.0, 1.0, 0.0);
	glRotatef(student1.head_angle[0], 1.0, 0.0, 0.0);

	glPushMatrix();
	change_color(COLOR_SKIN);
	glTranslatef(0.0, 4.0, 0.0);
	glScalef(8.0, 8.0, 8.0);
	draw_cube();
	glPopMatrix();

	draw_hair();
	draw_face();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 6.25, 0.0);
	glScalef(4.0, 0.5, 4.0);
	draw_cube();
	glPopMatrix();
}

void draw_hair(void)
{
	glPushMatrix();
	glColor3f(0.37, 0.15, 0.02);
	glPushMatrix();
	glTranslatef(0.0, 8.25, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2d(-4.25, -4.25);
		glVertex2d(4.25, -4.25);
		glVertex2d(4.25, 4.25);
		glVertex2d(-4.25, 4.25);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.25, 4.0, 0.0);
	glRotatef(-90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2d(-4.25, -1.0);
		glVertex2d(-3.0, -1.0);
		glVertex2d(-3.0, 0.0);
		glVertex2d(0.0, 0.0);
		glVertex2d(0.0, 1.0);
		glVertex2d(4.25, 1.0);
		glVertex2d(4.25, 4.25);
		glVertex2d(-4.25, 4.25);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.25, 4.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2d(4.25, -1.0);
		glVertex2d(4.25, 4.25);
		glVertex2d(-4.25, 4.25);
		glVertex2d(-4.25, 1.0);
		glVertex2d(0.0, 1.0);
		glVertex2d(0.0, 0.0);
		glVertex2d(3.0, 0.0);
		glVertex2d(3.0, -1.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 4.0, -4.25);
	glRotatef(180, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2d(-4.25, -1.0);
		glVertex2d(4.25, -1.0);
		glVertex2d(4.25, 4.25);
		glVertex2d(-4.25, 4.25);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 4.0, 4.25);
	glRotatef(0, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2d(-4.25, 1.0);
		glVertex2d(0.0, 1.0);
		glVertex2d(4.25, 3.0);
		glVertex2d(4.25, 4.25);
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
	glLineWidth(4.0);
	glTranslatef(0.0, 2.0, 4.01);
	glBegin(GL_LINE_STRIP);
		glVertex2f(-2.0, 0.0);
		glVertex2f(2.0, 0.0);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}

void draw_body(void)
{
	glPushMatrix();
	change_color(COLOR_GREEN);
	glScalef(8.0, 12.0, 4.0);
	draw_cube();
	glPopMatrix();
}

void draw_left_arm(void)
{
	draw_left_bicep();
	draw_left_forearm();
}

void draw_left_bicep(void)
{
	glPushMatrix();
	change_color(COLOR_GREEN);
	glTranslatef(4.0, 6.0, 0.0);
	glRotatef(15, 0.0, 0.0, 1.0);
	glTranslatef(2.0, -2.5, 0.0);
	glScalef(4.0, 5.0, 4.0);
	draw_cube();
	glPopMatrix();
}

void draw_left_forearm(void)
{
	glPushMatrix();
	change_color(COLOR_GREEN);
	glTranslatef(4.0 + (5.39 * sin(36.8 * M_PI / 180)), 6.0 - (5.39 * cos(36.8 * M_PI / 180)), 2.0);
	glRotatef(15, 0.0, 0.0, 1.0);
	glRotatef(-15, 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, -2.5, -2.0);
	glScalef(4.0, 5.0, 4.0);
	draw_cube();
	glPopMatrix();
	draw_left_hand();
	glPopMatrix();
}

void draw_left_hand(void)
{
	glPushMatrix();
	change_color(COLOR_SKIN);
	glTranslatef(0.0, -6.0, -2.0);
	glScalef(4.0, 2.0, 4.0);
	draw_cube();
	glPopMatrix();
}

void draw_right_arm(void)
{
	draw_right_bicep();
	draw_right_forearm();
}

void draw_right_bicep(void)
{
	glPushMatrix();
	change_color(COLOR_GREEN);
	glTranslatef(-4.0, 6.0, 0.0);
	glRotatef(-45, 0.0, 0.0, 1.0);
	glTranslatef(-2.0, -2.5, 0.0);
	glScalef(4.0, 5.0, 4.0);
	draw_cube();
	glPopMatrix();
}

void draw_right_forearm(void)
{
	glPushMatrix();
	change_color(COLOR_GREEN);
	glTranslatef(-4.0 - (5.39 * sin(66.8 * M_PI / 180)), 6.0 - (5.39 * cos(66.8 * M_PI / 180)), 2.0);
	glRotatef(-45, 0.0, 0.0, 1.0);
	glRotatef(-45, 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, -2.5, -2.0);
	glScalef(4.0, 5.0, 4.0);
	draw_cube();
	glPopMatrix();
	draw_right_hand();
	draw_phone();
	glPopMatrix();
}

void draw_right_hand(void)
{
	glPushMatrix();
	change_color(COLOR_SKIN);
	glTranslatef(0.0, -6.0, -2.0);
	glScalef(4.0, 2.0, 4.0);
	draw_cube();
	glPopMatrix();
}

void draw_left_leg(void)
{
	draw_left_thigh();
	draw_left_calf();
}

void draw_left_thigh(void)
{
	glPushMatrix();
	change_color(COLOR_BLUE);
	glTranslatef(2.0, -6.0, 2.0);
	glRotatef(-30, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -2.5, -2.0);
	glScalef(4.0, 5.0, 4.0);
	draw_cube();
	glPopMatrix();
}

void draw_left_calf(void)
{
	glPushMatrix();
	change_color(COLOR_BLUE);
	glTranslatef(2.0, -6.0 - (6.4 * sin((30 + 51.3) * M_PI / 180)), 2.0 + (6.4 * cos((30 * 51.3) * M_PI / 180)));
	glRotatef(0.0, 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, -2.5, 2.0);
	glScalef(4.0, 5.0, 4.0);
	draw_cube();
	glPopMatrix();
	draw_left_foot();
	glPopMatrix();
}

void draw_left_foot(void)
{
	glPushMatrix();
	change_color(COLOR_BROWN);
	glTranslatef(0.0, -6.0, 3.0);
	glScalef(4.0, 2.0, 6.0);
	draw_cube();
	glPopMatrix();
}

void draw_right_leg(void)
{
	draw_right_thigh();
	draw_right_calf();
}

void draw_right_thigh(void)
{
	glPushMatrix();
	change_color(COLOR_BLUE);
	glTranslatef(-2.0, -6.0, -2.0);
	glRotatef(30, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -2.5, 2.0);
	glScalef(4.0, 5.0, 4.0);
	draw_cube();
	glPopMatrix();
}

void draw_right_calf(void)
{
	glPushMatrix();
	change_color(COLOR_BLUE);
	glTranslatef(-2.0, -6.0 - (5.0 * cos(30 * M_PI / 180)), -2.0 - (5.0 * sin(30 * M_PI / 180)));
	glRotatef(60.0, 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, -2.5, 2.0);
	glScalef(4.0, 5.0, 4.0);
	draw_cube();
	glPopMatrix();
	draw_right_foot();
	glPopMatrix();
}

void draw_right_foot(void)
{
	glPushMatrix();
	change_color(COLOR_BROWN);
	glTranslatef(0.0, -6.0, 3.0);
	glScalef(4.0, 2.0, 6.0);
	draw_cube();
	glPopMatrix();
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
	glTranslatef(-0.2, -8.8, -1.49);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(3.0, 5.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.2, -9.8, -1.48);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.2, -8.8, -1.48);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.2, -7.8, -1.48);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.2, -9.8, -1.48);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	glColor3f(0.0, 0.5, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.2, -8.8, -1.48);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	glColor3f(0.5, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix(); 
	
	glPushMatrix();
	glTranslatef(-1.2, -7.8, -1.48);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.2, -9.8, -1.48);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	glColor3f(0.0, 0.0, 0.5);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.8, -9.8, -1.48);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix(); 
	
	glPushMatrix();
	glTranslatef(1.8, -8.8, -1.48);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	glColor3f(0.0, 1.0, 0.5);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix(); 
	
	glPushMatrix();
	glTranslatef(1.8, -7.8, -1.48);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.75, 0.75, 1.0);
	glColor3f(0.5, 0.0, 0.5);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix(); 
	
	glPushMatrix();
	glTranslatef(2.65, -8.8, -1.48);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.5, 0.5, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}

void draw_student(void)
{
	glTranslatef(student1.position[0], student1.position[1], student1.position[2]);
	glScalef(student1.scale, student1.scale, student1.scale);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(student1.angle[1], 0.0, 1.0, 0.0);

	draw_head();
	draw_body();
	draw_left_arm();
	draw_right_arm();
	draw_left_leg();
	draw_right_leg();
	draw_backpack();
}

void rotate_student(GLfloat theta, GLfloat phi)
{
	student1.angle[0] = (int)(student1.angle[0] + theta) % 360;
	student1.angle[1] = (int)(student1.angle[1] + phi) % 360;
}

void translate_student(GLfloat delta)
{
	student1.position[0] += delta * sin(student1.angle[1] * (M_PI / 180));
	student1.position[2] += delta * cos(student1.angle[1] * (M_PI / 180));
}

void scale_student(GLfloat factor)
{
	student1.scale = factor;
}

void rotate_head(GLfloat theta, GLfloat phi)
{
	if (abs((int)(student1.head_angle[0] + theta) % 360) < 45)
		student1.head_angle[0] = (int)(student1.head_angle[0] + theta) % 360;
	if (abs((int)(student1.head_angle[1] + phi) % 360) < 90)
		student1.head_angle[1] = (int)(student1.head_angle[1] + phi) % 360;
}

void reset_student(void)
{
	student1 = initial_student;
	glLoadIdentity();
}