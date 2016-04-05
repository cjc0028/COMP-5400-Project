/*
* Name: Chase Counsell
* Project: COMP 5400 Project 3
* File: Main.c 
* Date: 3/1/2016
* Description: Main program for rendering a 3D student.
*
* The functions for drawing cubes and its properties are declared in cube.h and defined in cube.c
* The functions for drawing the student are declared in student.h and defined in student.c
* The functions for controlling the camera are declared in camera.h and defined in camera.c
* The functions for drawing the buildings are declared in buildings.h and defined in buildings.c
* Currently limbs' positions are independent of each other, except the hands and feet.
* The hands and feet positions depend on the position of the forearm and calves respectively.
* The camera can also be rotated by moving the mouse while holding down the left mouse button.
* The bounds use a convex hull calculated by the x, y, and z of the building.
* Bounds are not calculated for the student yet.
* My design separates the view/projection from the models. This allows for more modularity.
* The student can be easily added to any project by copying over cube.c, cube.h, student.c, and student.c.
* Camera functions can be added to any project by copying over camera.c and camera.h.
*
* The controls for the student are:
* - UP - Tilt Head Forward
* - DOWN - Tilt Head Backward
* - RIGHT - Rotate Head Right
* - LEFT - Rotate Head Left
* - 'W' - Move Forward
* - 'S' - Move Backward
* - 'A' - Rotate Left
* - 'D' - Rotate Right
* - '1' - x1.0 Scale
* - '2' - x2.0 Scale
* - '5' - x0.5 Scale
* - 'M' - Toggle Mode
* - 'B' - Toggle Bounds
* - 'R' - Reset Position
* These controls are also printed on the screen.
*
*/

#define _USE_MATH_DEFINES
#include<math.h>
#include<GL\glut.h>
#include "student.h"
#include "cube.h"
#include "buildings.h"
#include "camera.h"

void toggle_mode(void);

static GLfloat ww = 800, wh = 800;                           // Initial window width and height
static GLfloat cw = 800, ch = 800;                           // Current window width and height
GLfloat aspect = 1.0;
static int mode = 0;                                         // 0 - student, 1 - camera
static int camera_mode = 0;                                  // 0 - Free Cam, 1 - 1st Person
static int originX = -1, originY = -1;                       // Position of mouse on click
static GLfloat theta = 0.0, phi = 0.0;                       // theta - horizontal angle, phi - vertical

void glInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}

void create_text(GLfloat x, GLfloat y, char *text)
{
	char *c;
	glRasterPos2f(x, y);
	for (c = text; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
	}
}

void draw_text(void)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluOrtho2D(0.0, cw, 0.0, ch);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(0.0, 0.0, 0.0);

	create_text(1.0, 103.0, "UP - Tilt Head Forward");
	create_text(1.0, 89.0, "DOWN - Tilt Head Backward");
	create_text(1.0, 75.0, "LEFT - Rotate Head Left");
	create_text(1.0, 61.0, "RIGHT - Rotate Head Right");
	create_text(1.0, 47.0, "W - Move Forward");
	create_text(1.0, 33.0, "S - Move Backward");
	create_text(1.0, 19.0, "A - Rotate Left");
	create_text(1.0, 5.0, "D - Rotate Right");
	create_text(cw - 115, 75.0, "1 - Scale 1.0");
	create_text(cw - 115, 61.0, "2 - Scale 2.0");
	create_text(cw - 115, 47.0, "5 - Scale 0.5");
	create_text(cw - 115, 33.0, "M - Toggle Mode");
	create_text(cw - 115, 19.0, "B - Toggle Bounds");
	create_text(cw - 115, 5.0, "R - Reset Position");
	if (mode == 0)
		create_text(cw - 115, ch - 15, "Mode: Student");
	else
		create_text(cw - 115, ch - 15, "Mode: Camera");

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	GLfloat *position = get_camera_position();
	GLfloat *target = get_camera_target();
	GLfloat *up = get_camera_up();

	gluLookAt(position[0], position[1], position[2],
		      target[0], target[1], target[2],
		      up[0], up[1], up[2]);

	glPushMatrix();
	draw_student();
	glPopMatrix();

	glPushMatrix();
	draw_buildings();
	glPopMatrix();

	draw_text();

	glFlush();
	glutSwapBuffers();
}

void myReshape(int w, int h)
{
	if (h == 0) h = 1;
	cw = w;
	ch = h;
	if (w >= h)
		aspect = (GLfloat)w / (GLfloat)h;
	else
		aspect = (GLfloat)h / (GLfloat)w;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{	
		case GLUT_KEY_UP:
			
			if (!mode) rotate_head(2.0, 0.0);
			else rotate_camera(0.0, 2.0);
			break;
		case GLUT_KEY_DOWN:
			if (!mode) rotate_head(-2.0, 0.0);
			else rotate_camera(0.0, -2.0);
			break;
		case GLUT_KEY_RIGHT:
			if (!mode) rotate_head(0.0, -2.0);
			else rotate_camera(2.0, 0.0);
			break;
		case GLUT_KEY_LEFT:
			if (!mode) rotate_head(0.0, 2.0);
			else rotate_camera(-2.0, 0.0);
			break;
		case GLUT_KEY_F1:
			camera_mode = !camera_mode;
		default:
			break;
	}

	glutPostRedisplay();
}

void keys(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'b':
		case 'B':
			toggle_bounds();
			break;
		case 'm':
		case 'M':
			//toggle_mode();
			mode = !mode;
			break;
		case 'r':
		case 'R':
			reset_student();
			reset_camera();
			break;
		case 'w':
		case 'W':
			if (!mode) translate_student(1.0);
			else translate_camera(5.0);
			break;
		case 's':
		case 'S':
			if (!mode) translate_student(-1.0);
			else translate_camera(-5.0);
			break;
		case 'a':
		case 'A':
			if (!mode && !camera_mode) rotate_student(0.0, 2.0);
			else rotate_camera(-2.0, 0.0);
			break;
		case 'd':
		case 'D':
			if (!mode) rotate_student(0.0, -2.0);
			else rotate_camera(2.0, 0.0);
			break;
		case '1':
			scale_student(1.0);
			break;
		case '2':
			scale_student(2.0);
			break;
		case '5':
			scale_student(0.5);
			break;
		default:
			break;
	}

	glutPostRedisplay();
}

void mouseMotion(int x, int y)
{
	if (originX && originY >= 0 && mode)
	{
		theta = ((x - originX) * 0.01) * 180 / M_PI;
		phi = ((y - originY) * 0.01) * 180 / M_PI;
		originX = x, originY = y;
		rotate_camera(theta, -phi);
	}
	glutPostRedisplay();
}

void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			GLfloat *angle = get_camera_angle();
			angle[0] += theta;
			angle[1] += phi;
			originX = -1, originY = -1;
		}
		else
		{
			originX = x, originY = y;
		}
	}
}

void toggle_mode(void)
{
	mode = !mode;
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh); /* 800 x 800 pixel window */
	glutCreateWindow("COMP-5/6400 Assignment 4");
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(keys);
	glutSpecialFunc(specialKeys);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	glutDisplayFunc(display);
	glInit();
	glutMainLoop();
}