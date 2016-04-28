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
* Console commands! I spent all my time on this and ran out of time for the other stuff.
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
* - F1 - Start tour
* These controls are also printed on the screen.
*
*/

#define _USE_MATH_DEFINES
#include<math.h>
#include<Windows.h>
#include<GL\glut.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<time.h>
#include<main.h>
#include "person.h"
#include "shapes.h"
#include "buildings.h"
#include "camera.h"
#include "lighting.h"
#include "command_prompt.h"
#include "command_processor.h"
#include "collisions.h"

static GLfloat ww = 800, wh = 800;															// Initial window width and height
static int window_id;																		// Main window id
static GLfloat aspect = 1.0;																// Window aspect ratio
static int control_mode = 0;																// 0 - student, 1 - camera
static int originX = -1, originY = -1;														// Position of mouse on click
static GLfloat theta = 0.0, phi = 0.0;														// theta - y axis rotation, phi - x axis rotation

static const GLfloat no_mat[4] = {0.0, 0.0, 0.0, 1.0};

int current_time = 0.0;
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
	if (control_mode == 0)
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
	GLfloat * position = get_camera_position();
	GLfloat * target = get_camera_target();
	GLfloat * up = get_camera_up();

	glLightfv(GL_LIGHT1, GL_POSITION, get_camera_position());

	gluLookAt(position[0], position[1], position[2],
				target[0], target[1], target[2],
				up[0], up[1], up[2]);

	glPushMatrix();
	glRotatef(current_time * 0.022, 0.0, 0.0, 1.0);
	glTranslatef(get_light_position(2)[0], get_light_position(2)[1], get_light_position(2)[2]);
	draw_sun_moon();
	glPopMatrix();

	glPushMatrix();
	draw_buildings();
	glPopMatrix();

	for (int i = 0; i < get_num_people(); i++)
	{
		glPushMatrix();
		draw_person(i);
		glPopMatrix();
	}

	draw_text();

	if(get_prompt_state()) draw_prompt();

	glFlush();
	glutSwapBuffers();
}

/// <summary>
/// Starts the tour.
/// </summary>
static void tour(void)
{
	set_camera_position(-100.0, 2.35, -225.0);
	reset_person();
	set_person_position(0, 3, -100.0, 18.0, -215.0);
	open_command_prompt();
	char str[100] = "";
	char welcome[10][100] = { "Hi! Welcome to my program!\r", "There's not much to see, but there's a lot of functionality!\r",
		"One of the coolest things about it is this console!\r", "Let's check it out!\r", "The first command you should know is \"/help\"\r",
	    "/help\r", "It lists all the main commands\r" };

	char commands[10][100] = { "Toggle can toggle the daylight or bounds\r", "Tour starts the tour you are on right now\r",
							   "And exit closes the program. Careful with that one!\r", "After that is the module commands\r",
	                           "Lighting controls the lighting and person controls the people. Duh.\r"};

	char lighting[10][100] = { "/lighting\r", "Lighting can do almost anything with lights!\r", "Disable them\r",
							   "/lighting disable 1\r", "Enable them\r", "/lighting enable 1\r", "Set allows you to change many properties of light",
	                           "/lighting set\r" };

	char person[10][100] = { "/person help\r", "Person commands control people\r", "Create them\r", "/person create student skin\r", 
	                         "Move them\r", "/person set position 2 -97.0 18.0 -215.0\r" };

	char done[10][100] = { "Well that's it\r", "There's a lot more I would like to implement, but didn't have time to\r",
						   "I hope you enjoyed!\r", "Bye!\r"};

	Sleep(100);
	for (int i = 0; i < 10; i++)
	{
		sprintf_s(str, 100, "%s", welcome[i]);
		for (u_int j = 0; j < strlen(str); j++)
		{
			write_to_prompt(str[j]);
			display();
		}
		clear_prompt();
	}

	Sleep(100);
	for (int i = 0; i < 10; i++)
	{
		sprintf_s(str, 100, "%s", commands[i]);
		for (u_int j = 0; j < strlen(str); j++)
		{
			write_to_prompt(str[j]);
			display();
		}
		clear_prompt();
	}

	Sleep(100);
	for (int i = 0; i < 10; i++)
	{
		sprintf_s(str, 100, "%s", lighting[i]);
		for (u_int j = 0; j < strlen(str); j++)
		{
			write_to_prompt(str[j]);
			display();
		}
		clear_prompt();
	}

	Sleep(100);
	for (int i = 0; i < 10; i++)
	{
		sprintf_s(str, 100, "%s", person[i]);
		for (u_int j = 0; j < strlen(str); j++)
		{
			write_to_prompt(str[j]);
			display();
		}
		clear_prompt();
	}

	write_to_prompt("/person set body_part_angle 0 HEAD 0 -45 0\r");

	Sleep(100);
	for (int i = 0; i < 10; i++)
	{
		sprintf_s(str, 100, "%s", done[i]);
		for (u_int j = 0; j < strlen(str); j++)
		{
			write_to_prompt(str[j]);
			display();
		}
		clear_prompt();
	}
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
			if (!control_mode) rotate_head(-get_person(get_selected_person()).rotation_speed, 0.0);
			else rotate_camera(0.0, get_camera_rotation_speed());
			break;
		case GLUT_KEY_DOWN:
			if (!control_mode) rotate_head(get_person(get_selected_person()).rotation_speed, 0.0);
			else rotate_camera(0.0, -get_camera_rotation_speed());
			break;
		case GLUT_KEY_RIGHT:
			if (!control_mode) rotate_head(0.0, -get_person(get_selected_person()).rotation_speed);
			else rotate_camera(get_camera_rotation_speed(), 0.0);
			break;
		case GLUT_KEY_LEFT:
			if (!control_mode) rotate_head(0.0, get_person(get_selected_person()).rotation_speed);
			else rotate_camera(-get_camera_rotation_speed(), 0.0);
			break;
		case GLUT_KEY_F1:
			tour();
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
			if (!control_mode) rotate_person(0.0, get_person(get_selected_person()).rotation_speed);
			else
			{
				if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) strafe_camera(-get_camera_speed());
				else rotate_camera(-get_camera_rotation_speed(), 0.0);
				if (collision_detected(get_camera_bounds())) strafe_camera(get_camera_speed());
			}
			break;
		case 'b':
		case 'B':
			toggle_bounds();
			break;
		case 'c':
		case 'C':
			create_light(1, get_camera_position());
			break;
		case 'd':
		case 'D':
			if (!control_mode) rotate_person(0.0, -get_person(get_selected_person()).rotation_speed);
			else
			{
				if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) strafe_camera(get_camera_speed());
				else rotate_camera(get_camera_rotation_speed(), 0.0);
				if (collision_detected(get_camera_bounds())) strafe_camera(-get_camera_speed());
			}
			break;
		case 'l':
		case 'L':
			toggle_lights();
			break;
		case 'm':
		case 'M':
			control_mode = !control_mode;
			break;
		case 'r':
		case 'R':
			reset_camera();
			reset_person();
			break;
		case 's':
		case 'S':
			if (!control_mode)
			{
				translate_person(-get_person(get_selected_person()).speed);
				if (collision_detected(get_bounds())) translate_person(get_person(get_selected_person()).speed);
			}
			else
			{
				translate_camera(-get_camera_speed());
				if (collision_detected(get_camera_bounds())) translate_camera(get_camera_speed());
			}
			break;
		case 'w':
		case 'W':
			if (!control_mode)
			{
				translate_person(get_person(get_selected_person()).speed);
				if (collision_detected(get_bounds())) translate_person(-get_person(get_selected_person()).speed);
			}
			else
			{
				translate_camera(get_camera_speed());
				if (collision_detected(get_camera_bounds())) translate_camera(-get_camera_speed());
			}
			break;
		case '1':
			scale_person(1.0);
			break;
		case '2':
			scale_person(2.0);
			break;
		case '5':
			scale_person(0.5);
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
		case '\r':
			open_command_prompt();
			break;
		case ' ':
			if (!control_mode && !get_people()[get_selected_person()].in_air) jump(get_selected_person());
			else if (control_mode)
			{
				if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
				{
					elevate_camera(-get_camera_speed());
					if (collision_detected(get_camera_bounds())) elevate_camera(get_camera_speed());
				}
				else
				{
					elevate_camera(get_camera_speed());
					if (collision_detected(get_camera_bounds())) elevate_camera(-get_camera_speed());
				}
			}
			break;
		default:
			break;
		}

		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
		{
			elevate_camera(-get_camera_speed());
		}
	}
	else if (key == 27)
	{
		close_command_prompt();
	}
	else if (key == 13)
	{
		write_to_prompt(key);
	}
	else
	{
		write_to_prompt(key);
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
/// OpenGL timer callback functions.
/// </summary>
/// <param name="fps">Frame limit for program.</param>
void timer(int fps)
{
	float t = 0.1;
	if (get_people()[get_selected_person()].in_air)
	{
		get_people()[get_selected_person()].position[1] += (-GRAVITY * t * t) + (get_people()[get_selected_person()].velocity[1] * t);
		get_people()[get_selected_person()].velocity[1] += (-GRAVITY * t);
		if (get_people()[get_selected_person()].position[1] <= 18.0)
		{
			get_people()[get_selected_person()].in_air = 0;
			get_people()[get_selected_person()].position[1] = 18.0;
		}
	}

	if (daylight_cycle) current_time += 1;
	if (current_time > 8191)
	{
		current_time = 0;
		toggle_daylight();
	}

	glutPostRedisplay();
	glutTimerFunc(1000 / fps, timer, fps);
}

/// <summary>
/// Handles main program console commands
/// </summary>
/// <param name="command">The command to be run.</param>
void main_commands(int num_args, char * args[])
{
	if (_stricmp(args[0], "clear") == 0)
	{
		clear_history();
	}
	else if (_stricmp(args[0], "toggle") == 0)
	{
		if (num_args == 1 && _stricmp(args[1], "daylight") == 0)
		{
			toggle_daylight();
		}
		else if (num_args == 1 && _stricmp(args[1], "bounds") == 0)
		{
			toggle_bounds();
		}
		else if (num_args == 1 && _stricmp(args[1], "control") == 0)
		{
			control_mode = !control_mode;
			if (control_mode) print_command("Switched to camera control");
			else print_command("Switched to person control");
		}
		else
		{
			char str_usage[100] = "Usage: Toggles a state";
			print_command("");
			print_command(str_usage);
			sprintf_s(str_usage, 100, "\"/toggle {daylight | bounds | control}\"");
			print_command(str_usage);
		}
	}
	else if (_stricmp(args[0], "tour") == 0)
	{
		clear_prompt();
		tour();
	}
	else if (_stricmp(args[0], "exit") == 0)
	{
		glutDestroyWindow(window_id);
		exit(0);
	}
	else
	{
		Command * commands = get_commands();
		char str[20] = "/";

		print_command("");
		print_command("List of commands:");
		for (int i = 0; i < get_num_commands(); i++)
		{
			sprintf_s(str, 20, "/%s", commands[i].name);
			print_command(str);
		}
	}
}

/// <summary>
/// Initializes main console commands
/// </summary>
static void initialize_main_commands(void)
{
	add_command("clear", &main_commands);
	add_command("help", &main_commands);
	add_command("toggle", &main_commands);
	add_command("tour", &main_commands);
	add_command("exit", &main_commands);
}

/// <summary>
/// OpenGL one-time initialization.
/// </summary>
void glInit(void)
{
	glClearColor(0.015, 0.463, 0.851, 1.0);
	glClearDepth(1.0f);
	myReshape(ww, wh);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	initialize_main_commands();

	GLfloat lightPos0[] = { 0.0f, 2.0f, 4.0f, 1.0f };
	GLfloat lightPos1[] = { -100.0f, 10.0f, 0.0f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat spotDir0[] = { 0.0f, 0.0f, -1.0f };
	GLfloat spotDir1[] = { 0.0f, 0.0f, -1.0f };

	GLfloat sun_pos[4] = { 500.0, 0.0, 0.0, 1.0 };
	GLfloat sun_ambient[4] = { 0.1, 0.1, 0.0, 1.0 };
	GLfloat sun_diffusion[4] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat sun_specular[4] = { 0.2, 0.2, 0.2, 1.0 };

	initialize_lighting();
	create_spotlight(7, lightPos0, ambientLight, diffuse, specular, spotDir0, 15.0, 100.0); //Spotlight on main student
	create_spotlight(7, lightPos1, ambientLight, diffuse, specular, spotDir1, 15.0, 100.0);
	create_light(4, sun_pos, sun_ambient, sun_diffusion, sun_specular);

	initialize_people();
	create_student(0);
	create_bystander(0);
	set_person_position(1, 3, -100.0, 18.0, -200.0);

	clear_history();
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
	window_id = glutCreateWindow("COMP-5/6400 Assignment 5");
	glInit();
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(keys);
	glutSpecialFunc(specialKeys);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	glutDisplayFunc(display);
	glutTimerFunc(1000, timer, FPS);
	glutMainLoop();
}