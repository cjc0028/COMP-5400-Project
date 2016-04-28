/*
* Name: Chase Counsell
* Project: COMP 5400 Project 4
* File: commands.c
* Date: 4/17/2016
* Description: Functions for creating text commands
*/


#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<GL/glut.h>
#include "command_prompt.h"
#include "command_processor.h"

#define BUFFER_SIZE 100
#define C_HISTORY_SIZE 30

static int prompt_state = PROMPT_CLOSE;

typedef struct Buffer
{
	char string[BUFFER_SIZE];
	int length;
}Buffer;

static Buffer buffer;
static char command_history[C_HISTORY_SIZE][BUFFER_SIZE];
static int command_history_size = 0;
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
	selected_buffer_index = 0;
	memset(buffer.string, 0, sizeof buffer.string);
}

void clear_prompt(void)
{
	buffer.length = 0;
	selected_buffer_index = 0;
	memset(buffer.string, 0, sizeof buffer.string);
}

void clear_history(void)
{
	for (int i = 0; i < C_HISTORY_SIZE; i++)
	{
		memset(command_history[i], 0, sizeof command_history[i]);
	}
	command_history_size = 0;
}

int get_prompt_state(void)
{
	return prompt_state;
}

void print_command_history(void)
{
	glColor3f(1.0, 1.0, 1.0);
	for (int i = command_history_size; i > 0; i--)
	{
		int length = strlen(command_history[command_history_size - i]);
		glRasterPos2i(2.0, 9.0 + (i * 13));
		for (int j = 0; j < length; j++)
		{
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, command_history[command_history_size - i][j]);

			glRasterPos2i(2.0 + ((j + 1) * 9), 9.0 + (i * 13));
		}
	}
}

static void print_buffer(void)
{
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(2.0, 5.0);
	for (int i = 0; i < buffer.length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, buffer.string[i]);

		glRasterPos2i(2.0 + ((i + 1) * 9), 5.0);
	}
}

static void set_cursor(void)
{
	glColor3f(0.0, 0.0, 0.0);
	glGetIntegerv(GL_CURRENT_RASTER_POSITION, cursor_pos);
	cursor_pos[0] += (9 * cursor_offset);
	glBegin(GL_POLYGON);
		glVertex2f(cursor_pos[0], cursor_pos[1] - 4);
		glVertex2f(cursor_pos[0] + 1, cursor_pos[1] - 4);
		glVertex2f(cursor_pos[0] + 1, cursor_pos[1] + 9);
		glVertex2f(cursor_pos[0], cursor_pos[1] + 9);
	glEnd();
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

	glColor4f(0.0, 0.0, 0.0, 0.7);
	glBegin(GL_POLYGON);
		glVertex2d(0.0, 15.0);
		glVertex2d(glutGet(GLUT_WINDOW_WIDTH), 15.0);
		glVertex2d(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) / 2.0);
		glVertex2d(0.0, glutGet(GLUT_WINDOW_HEIGHT) / 2.0);
	glEnd();

	print_command_history();

	print_buffer();

	set_cursor();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}

void write_to_prompt(unsigned char c)
{
	if (buffer.length > 0 && c == 8 && selected_buffer_index != 0)
	{
		buffer.string[selected_buffer_index-1] = '\0';
		buffer.length--;
		for (int i = selected_buffer_index-1; i < buffer.length; i++)
		{
			buffer.string[i] = buffer.string[i + 1];
		}
	}
	else if (buffer.length != 0 && c == '\r')
	{
		run_command();
		buffer.length = 0;
		selected_buffer_index = 0;
		memset(buffer.string, 0, sizeof buffer.string);
	}
	else if (c == '\r') close_command_prompt();
	else if (c != 8)
	{
		if (buffer.length < BUFFER_SIZE)
		{
			buffer.length++;
			for (int i = buffer.length - 1; i > selected_buffer_index; i--)
			{
				buffer.string[i] = buffer.string[i - 1];
			}
			buffer.string[selected_buffer_index] = c;
		}
	}
	
	selected_buffer_index = buffer.length + cursor_offset;
}

void write_to_command_history(char * text)
{
	if (command_history_size == C_HISTORY_SIZE)
	{
		for (int i = 0; i < C_HISTORY_SIZE - 1; i++)
		{
			//command_history[i] = command_history[i + 1];
			strcpy_s(command_history[i], 100, command_history[i + 1]);
		}
		strcpy_s(command_history[C_HISTORY_SIZE - 1], 100, text);
	}
	else
	{
		strcpy_s(command_history[command_history_size], 100, text);
		command_history_size++;
	}
}

void move_cursor(int key)
{
	if (key == GLUT_KEY_LEFT && abs(cursor_offset) < buffer.length) cursor_offset -= 1;
	else if (key == GLUT_KEY_RIGHT && cursor_offset < 0) cursor_offset += 1;

	selected_buffer_index = buffer.length + cursor_offset;
}

void run_command(void)
{
	if (buffer.length > 0 && buffer.string[0] != '/')
	{
		char str[100];
		sprintf_s(str, 100, "<User>: %s", buffer.string);
		write_to_command_history(str);
	}
	else
	{
		int num_args = 0;
		char * str = buffer.string;
		const char * delim = " /";
		char * next_token;
		char * tokens[10] = {0};

		char * token = strtok_s(str, delim, &next_token);
		while (token)
		{
			tokens[num_args++] = token;
			token = strtok_s(NULL, delim, &next_token);
		}

		process_command(num_args, tokens);
	}
}