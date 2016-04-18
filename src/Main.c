/*
* Name: Chase Counsell
* Project: COMP 5400 Project
* File: Main.c 
* Date: 3/1/2016
* Description: Main program for rendering a 3D environment.
*
* The functions for drawing cubes and its properties are declared in cube.h and defined in cube.c
* The functions for drawing the student are declared in student.h and defined in student.c
* The functions for controlling the camera are declared in camera.h and defined in camera.c
* The functions for drawing the buildings are declared in buildings.h and defined in buildings.c
* Limbs' positions are dependent of each other.
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
#include<stdlib.h>
#include<time.h>
#include "person.h"
#include "cube.h"
#include "buildings.h"
#include "camera.h"
#include "lighting.h"
#include "commands.h"


static GLfloat ww = 800, wh = 800; // Initial window width and height
static GLfloat aspect = 1.0;
static int mode = 0; // 0 - student, 1 - camera
static int camera_mode = 0; // 0 - Free Cam, 1 - 1st Person
static int originX = -1, originY = -1; // Position of mouse on click
static GLfloat theta = 0.0, phi = 0.0; // theta - y axis rotation, phi - x axis rotation
static GLfloat ground_size[4];

static const GLfloat no_mat[4] = {0.0, 0.0, 0.0, 1.0};

GLfloat lightPos0[] = {0.0f, 2.0f, 4.0f, 1.0f};
GLfloat lightPos1[] = {-110.0f, 10.0f, 0.0f, 1.0f};
GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat spotDir0[] = {0.0f, 0.0f, -1.0f};
GLfloat spotDir1[] = {0.0f, -1.0f, 0.0f};

GLfloat sun_pos[4] = {500.0, 0.0, 0.0, 1.0};
GLfloat sun_ambient[4] = {0.1, 0.1, 0.0, 1.0};
GLfloat sun_diffusion[4] = {0.5, 0.5, 0.5, 1.0};
GLfloat sun_specular[4] = {0.2, 0.2, 0.2, 1.0};
GLfloat current_time = 0.0;
int daylight_cycle = 1;


/// <summary>
/// Draws text at the specified x and y coordinates.
/// </summary>
/// <param name="x">The x coordinate.</param>
/// <param name="y">The y coordinate.</param>
/// <param name="text">The text to be drawn.</param>
void create_text(GLfloat x, GLfloat y, char* text)
{
	char* c;
	glRasterPos2f(x, y);
	for (c = text; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
	}
}

/// <summary>
/// Draws all text on screen.
/// </summary>
void draw_text(void)
{
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, 800);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	create_text(1.0, 103.0, "UP - Tilt Head Forward");
	create_text(1.0, 89.0, "DOWN - Tilt Head Backward");
	create_text(1.0, 75.0, "LEFT - Rotate Head Left");
	create_text(1.0, 61.0, "RIGHT - Rotate Head Right");
	create_text(1.0, 47.0, "W - Move Forward");
	create_text(1.0, 33.0, "S - Move Backward");
	create_text(1.0, 19.0, "A - Rotate Left");
	create_text(1.0, 5.0, "D - Rotate Right");

	create_text(glutGet(GLUT_WINDOW_WIDTH) - 118, 103.0, "+/- Change Intensity");
	create_text(glutGet(GLUT_WINDOW_WIDTH) - 115, 89.0, "L - Toggle Lights");
	create_text(glutGet(GLUT_WINDOW_WIDTH) - 115, 75.0, "1 - Scale 1.0");
	create_text(glutGet(GLUT_WINDOW_WIDTH) - 115, 61.0, "2 - Scale 2.0");
	create_text(glutGet(GLUT_WINDOW_WIDTH) - 115, 47.0, "5 - Scale 0.5");
	create_text(glutGet(GLUT_WINDOW_WIDTH) - 115, 33.0, "M - Toggle Mode");
	create_text(glutGet(GLUT_WINDOW_WIDTH) - 115, 19.0, "B - Toggle Bounds");
	create_text(glutGet(GLUT_WINDOW_WIDTH) - 115, 5.0, "R - Reset Position");
	if (mode == 0)
		create_text(glutGet(GLUT_WINDOW_WIDTH) - 85, 785, "Mode: Student");
	else
		create_text(glutGet(GLUT_WINDOW_WIDTH) - 100, 785, "Mode: Camera");

	create_text(1.0, 785.0, get_lighting_mode());

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}

/// <summary>
/// Displays all objects to be drawn.
/// </summary>
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLfloat* position = get_camera_position();
	GLfloat* target = get_camera_target();
	GLfloat* up = get_camera_up();

	gluLookAt(position[0], position[1], position[2],
	          target[0], target[1], target[2],
	          up[0], up[1], up[2]);

	glPushMatrix();
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	if (daylight_cycle) current_time += (0.01);
	if (current_time >= 90.0)
	{
		current_time = -90.0;
		toggle_daylight();
	}
	glRotatef(current_time, 0.0, 0.0, 1.0);
	glTranslatef(sun_pos[0], sun_pos[1], sun_pos[2]);
	draw_sun_moon();
	glPopMatrix();

	glPushMatrix();
	//draw_student();
	glPopMatrix();

	glPushMatrix();
	draw_buildings();
	glPopMatrix();

	glPushMatrix();
	//draw_bystander();
	glPopMatrix();

	draw_text();

	if(get_prompt_state()) draw_prompt();

	glFlush();
	glutSwapBuffers();
}

/// <summary>
/// Reshape callback function.
/// </summary>
/// <param name="w">The screen width.</param>
/// <param name="h">The screen height.</param>
void myReshape(int w, int h)
{
	if (h == 0) h = 1;
	//cw = w;
	//ch = h;
	if (w >= h)
		aspect = (GLfloat)w / (GLfloat)h;
	else
		aspect = (GLfloat)h / (GLfloat)w;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/// <summary>
/// Non-ASCII key callback function.
/// </summary>
/// <param name="key">The pressed key.</param>
/// <param name="x">The mouse x coordinate.</param>
/// <param name="y">The mouse y coordinate.</param>
void specialKeys(int key, int x, int y)
{
	if (!get_prompt_state())
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
			break;
		default:
			break;
		}
	}
	else
	{
		if (key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT) move_cursor(key);
	}

	glutPostRedisplay();
}

/// <summary>
/// ASCII key callback function.
/// </summary>
/// <param name="key">The pressed key.</param>
/// <param name="x">The mouse x coordinate.</param>
/// <param name="y">The mouse y coordinate.</param>
void keys(unsigned char key, int x, int y)
{
	if (!get_prompt_state())
	{
		switch (key)
		{
		case 'a':
		case 'A':
			if (!mode && !camera_mode) rotate_student(0.0, 2.0);
			else rotate_camera(-2.0, 0.0);
			break;
		case 'b':
		case 'B':
			toggle_bounds();
			break;
		case 'c':
		case 'C':
			create_light(lightPos0, ambientLight, ambientLight, specular);
			break;
		case 'd':
		case 'D':
			if (!mode) rotate_student(0.0, -2.0);
			else rotate_camera(2.0, 0.0);
			break;
		case 'l':
		case 'L':
			toggle_lights();
			break;
		case 'm':
		case 'M':
			mode = !mode;
			break;
		case 'r':
		case 'R':
			reset_student();
			reset_camera();
			break;
		case 's':
		case 'S':
			if (!mode)
			{
				//GLfloat position[3] = { *get_position(), *(get_position() + 1), *(get_position() + 2) };
				//if ((position[0]-1.0 > ground_size[0]-1.0) && (position[0]-1.0 < ground_size[1]+1.0))
				//if ((position[2]-1.0 > ground_size[2]-1.0) && (position[2]-1.0 < ground_size[3]+1.0))
				{
					translate_student(-1.0);
				}
			}
			else
			{
				//GLfloat position[3] = { *get_camera_position(), *(get_camera_position() + 1), *(get_camera_position() + 2) };
				//if ((position[0]-1.0 > ground_size[0]-1.0) && (position[0]-1.0 < ground_size[1]+1.0))
				//if ((position[2]-1.0 > ground_size[2]-1.0) && (position[2]-1.0 < ground_size[3]+1.0))
				{
					translate_camera(-1.0);
				}
			}
			break;
		case 'w':
		case 'W':
			if (!mode)
			{
				//GLfloat position[3] = { *get_position(), *(get_position() + 1), *(get_position() + 2) };
				//if ((position[0]+1.0 > ground_size[0]-1.0) && (position[0]+1.0 < ground_size[1]+1.0))
				//if ((position[2]+1.0 > ground_size[2]-1.0) && (position[2]+1.0 < ground_size[3]+1.0))
				{
					translate_student(1.0);
				}
			}
			else
			{
				//GLfloat position[3] = { *get_camera_position(), *(get_camera_position() + 1), *(get_camera_position() + 2) };
				//if ((position[0]+1.0 > ground_size[0]-1.0) && (position[0]+1.0 < ground_size[1]+1.0))
				//if ((position[2]+1.0 > ground_size[2]-1.0) && (position[2]+1.0 < ground_size[3]+1.0))
				{
					translate_camera(1.0);
				}
			}
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
		case '=':
		case '+':
			change_intensity(0.5);
			break;
		case '-':
		case '_':
			change_intensity(-0.5);
			break;
		case '/':
			open_command_prompt();
			write_to_prompt(key);
			break;
		default:
			break;
		}
	}
	else if (key == 27)
	{
		close_command_prompt();
	}
	else
	{
		write_to_prompt(key);
	}
	if (key == 13)
	{
		if (!get_prompt_state())
			open_command_prompt();
		else
		{
			write_to_prompt(32);
			write_to_prompt(key);
			close_command_prompt();
		}
	}

	glutPostRedisplay();
}

/// <summary>
/// Mouse motion callback function.
/// </summary>
/// <param name="x">The mouse x coordinate.</param>
/// <param name="y">The mouse y coordinate.</param>
void mouseMotion(int x, int y)
{
	if (originX && originY >= 0)
	{
		theta = ((x - originX) * 0.01) * 180 / M_PI ;
		phi = ((y - originY) * 0.01) * 180 / M_PI ;
		originX = x , originY = y;
		rotate_camera(theta, -phi);
	}
	glutPostRedisplay();
}

/// <summary>
/// Mouse button callback function.
/// </summary>
/// <param name="button">The mouse button pressed.</param>
/// <param name="state">The up/down state of the mouse button.</param>
/// <param name="x">The mouse x coordinate.</param>
/// <param name="y">The mouse y coordinate.</param>
void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			GLfloat* angle = get_camera_angle();
			angle[0] += theta;
			angle[1] += phi;
			originX = -1 , originY = -1;
		}
		else
		{
			originX = x , originY = y;
		}
	}
}

/// <summary>
/// OpenGL one-time initialization.
/// </summary>
void glInit(void)
{
	//glClearColor(0.015, 0.463, 0.851, 1.0);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0f);
	myReshape(ww, wh);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	initialize_lighting();
	create_spotlight(lightPos0, ambientLight, diffuse, specular, 15.0, 100.0, spotDir0);
	create_spotlight(lightPos1, ambientLight, diffuse, specular, 45.0, 1000.0, spotDir1);
	create_light(sun_pos, sun_ambient, sun_diffusion, sun_specular);

	ground_size[0] = *get_ground_size();
	ground_size[1] = *(get_ground_size() + 1);
	ground_size[2] = *(get_ground_size() + 2);
	ground_size[3] = *(get_ground_size() + 3);
}

/// <summary>
/// Main program.
/// </summary>
/// <param name="argc">The number of command line arguments.</param>
/// <param name="argv">The argument array pointer.</param>
void main(int argc, char** argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh); /* 800 x 800 pixel window */
	glutCreateWindow("COMP-5/6400 Assignment 5");
	glInit();
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(keys);
	glutSpecialFunc(specialKeys);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
}

