/*
* Name: Chase Counsell
* Project: COMP 5400 Project 4
* File: cube.c
* Date: 3/1/2016
* Description: Functions for drawing a cube, changing the color, and toggling bounding box.
*/

#include<GL\glut.h>
#include "cube.h"

GLfloat vertices[][3] = { { -0.5, -0.5, -0.5 },{ 0.5, -0.5, -0.5 },{ 0.5, 0.5, -0.5 },
						  { -0.5, 0.5, -0.5 },{ -0.5, -0.5, 0.5 },{ 0.5, -0.5, 0.5 },
						  { 0.5, 0.5, 0.5 },{ -0.5, 0.5, 0.5 } };

GLfloat normals[][3] = { { -0.5, -0.5, -0.5 },{ 0.5, -0.5, -0.5 },{ 0.5, 0.5, -0.5 },
						 { -0.5, 0.5, -0.5 },{ -0.5, -0.5, 0.5 },{ 0.5, -0.5, 0.5 },
						 { 0.5, 0.5, 0.5 },{ -0.5, 0.5, 0.5 } };

GLfloat colors[][3] = { { 1.0, 0.80, 0.58 },{ 1.0, 0.0, 0.0 },{ 0.37, 0.15, 0.02 },
						{ 0.0, 0.5, 0.0 },{ 0.0, 0.0, 0.5 },{ 0.5, 0.5, 0.5 },
						{ 1.0, 1.0, 1.0 },{ 0.94, 0.43, 0.12 } };
enum color { skin, red, brown, green, blue, gray, white, orange };
static int current_color = skin;
static int is_bounding_enabled = 0;

void cube_face(int a, int b, int c, int d)
{
	/* draw a polygon via list of vertices */
	glBegin(GL_POLYGON);
		glColor3fv(colors[current_color]);
		glNormal3fv(normals[a]);
		glVertex3fv(vertices[a]);
		glColor3fv(colors[current_color]);
		glNormal3fv(normals[b]);
		glVertex3fv(vertices[b]);
		glColor3fv(colors[current_color]);
		glNormal3fv(normals[c]);
		glVertex3fv(vertices[c]);
		glColor3fv(colors[current_color]);
		glNormal3fv(normals[d]);
		glVertex3fv(vertices[d]);
	glEnd();
}

void draw_cube(void)
{
	cube_face(0, 1, 2, 3);
	cube_face(2, 3, 7, 6);
	cube_face(0, 4, 7, 3);
	cube_face(1, 2, 6, 5);
	cube_face(4, 5, 6, 7);
	cube_face(0, 1, 5, 4);
}

void change_color(int x)
{
	switch (x)
	{
	case 0:
		current_color = skin;
		break;
	case 1:
		current_color = red;
		break;
	case 2:
		current_color = brown;
		break;
	case 3:
		current_color = green;
		break;
	case 4:
		current_color = blue;
		break;
	case 5:
		current_color = gray;
		break;
	case 6:
		current_color = white;
		break;
	case 7:
		current_color = orange;
		break;
	default:
		current_color = skin;
		break;
	}
}

void toggle_bounds()
{
	is_bounding_enabled = !is_bounding_enabled;
}

int bounds_enabled()
{
	return is_bounding_enabled;
}