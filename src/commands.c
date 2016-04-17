/*
* Name: Chase Counsell
* Project: COMP 5400 Project 4
* File: commands.c
* Date: 4/17/2016
* Description: Functions for creating text commands
*/


#include<stdlib.h>
#include<GL/glut.h>
#include "commands.h"


#define BUFFER_SIZE 100
static int prompt_state = PROMPT_CLOSE;

typedef struct Buffer
{
	char string[BUFFER_SIZE];
	int length;
}Buffer;

static Buffer buffer;

void open_command_prompt(void)
{
	prompt_state = PROMPT_OPEN;
}

void close_command_prompt(void)
{
	prompt_state = PROMPT_CLOSE;
	buffer.length = 0;
	memset(buffer.string, 0, sizeof buffer.string);
}

int get_prompt_state(void)
{
	return prompt_state;
}

void draw_prompt(void)
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
	glBegin(GL_POLYGON);
		glVertex2d(0.0, 0.0);
		glVertex2d(glutGet(GLUT_WINDOW_WIDTH), 0.0);
		glVertex2d(glutGet(GLUT_WINDOW_WIDTH), 15.0);
		glVertex2d(0.0, 15.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	for (int i = 0; i < buffer.length; i++)
	{
		glRasterPos2f(2.0 + (i * 7), 4.0);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, buffer.string[i]);
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}

void write_to_prompt(unsigned char c)
{
	if (buffer.length > 0 && c == 8)
	{
		buffer.string[--buffer.length] = '0';
	}
	else if (c != 8)
	{
		if (buffer.length < BUFFER_SIZE)
			buffer.string[buffer.length++] = c;
	}
}