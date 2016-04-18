/*
* Name: Chase Counsell
* Project: COMP 5400 Project 4
* File: commands.c
* Date: 4/17/2016
* Description: Functions for creating text commands
*/


#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#include "commands.h"
#include "person.h"
#include "camera.h"
#include "buildings.h"
#include "lighting.h"

#define BUFFER_SIZE 100

static int prompt_state = PROMPT_CLOSE;
static char* modules[] = {"person", "buildings", "camera", "lighting"};

typedef struct Buffer
{
	char string[BUFFER_SIZE];
	int length;
}Buffer;

static Buffer buffer;
GLint cursor_pos[2];
static GLint cursor_offset = 0;
static int selected_buffer_index = 0;

void open_command_prompt(void)
{
	prompt_state = PROMPT_OPEN;
	cursor_offset = 0.0;
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
	glRasterPos2i(2.0, 5.0);
	for (int i = 0; i < buffer.length; i++)
	{
		if (i == selected_buffer_index)
		{
			//glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, buffer.string[i]);
			//glPopMatrix();
		}
		else
		{
			//glPushMatrix();
			glColor3f(0.0, 0.0, 0.0);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, buffer.string[i]);
			//glPopMatrix();
		}

		glRasterPos2i(2.0 + ((i+1) * 9), 4.0);
	}

	glColor3f(0.0, 0.0, 0.0);
	glGetIntegerv(GL_CURRENT_RASTER_POSITION, cursor_pos);
	cursor_pos[0] += (9 * cursor_offset);
	glBegin(GL_POLYGON);
		glVertex2f(cursor_pos[0], cursor_pos[1] - 4);
		glVertex2f(cursor_pos[0] + 9, cursor_pos[1] - 4);
		glVertex2f(cursor_pos[0] + 9, cursor_pos[1] + 9);
		glVertex2f(cursor_pos[0], cursor_pos[1] + 9);
	glEnd();

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
		buffer.string[selected_buffer_index] = '0';
		buffer.length--;
		for (int i = selected_buffer_index; i < buffer.length; i++)
		{
			buffer.string[i] = buffer.string[i + 1];
		}

		//buffer.string[buffer.length] = '0';
	}
	else if (c != 8)
	{
		if (buffer.length < BUFFER_SIZE)
		{
			buffer.length++;
			for (int i = buffer.length; i > selected_buffer_index; i--)
			{
				//char temp = buffer.string[i + 1];
				buffer.string[i] = buffer.string[i - 1];
			}
			buffer.string[selected_buffer_index] = c;
		}
	}

	selected_buffer_index = buffer.length + cursor_offset;
}

void move_cursor(int key)
{
	if (key == GLUT_KEY_LEFT && abs(cursor_offset) < buffer.length) cursor_offset -= 1;
	else if (key == GLUT_KEY_RIGHT && cursor_offset < 0) cursor_offset += 1;

	selected_buffer_index = buffer.length + cursor_offset;
}

void run_command(void)
{
	if (buffer.string[0] != '/')
	{

	}
	else
	{

	}
}