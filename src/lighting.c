/*
* Name: Chase Counsell
* Project: COMP 5400 Project 4
* File: lighting.c
* Date: 3/17/2016
* Description: Functions for controlling the lighting
*/

#define _USE_MATH_DEFINES
#define MAX_LIGHTS 8
#include<math.h>
#include<GL/glut.h>
#include "lighting.h"

typedef struct Light
{
	GLfloat position[4];
	GLfloat ambient[4];
	GLfloat diffusion[4];
	GLfloat specular[4];
}Light;

typedef enum LIGHTING_MODE {NO_LIGHTS, ONE_LIGHT, TWO_LIGHTS, ALL_LIGHTS} LIGHTING_MODE;
LIGHTING_MODE current_lighting_mode = NO_LIGHTS;
char * current_lighting_text = "ALL LIGHTS";
static Light lights[MAX_LIGHTS];
static int num_lights = 0;
static GLfloat global_ambient[4] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

void initialize_lighting(void)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
}

void create_light(GLfloat position[4], GLfloat ambient[4], GLfloat diffusion[4], GLfloat specular[4])
{
	Light new_light = {.position[0] = position[0], .position[1] = position[1], .position[2] = position[2] + 4.1, .position[3] = position[3],
		               .ambient[0] = ambient[0], .ambient[1] = ambient[1], .ambient[2] = ambient[2], .ambient[3] = ambient[3],
		               .diffusion[0] = diffusion[0], .diffusion[1] = diffusion[1], .diffusion[2] = diffusion[2], .diffusion[3] = diffusion[3],
		               .specular[0] = specular[0], .specular[1] = specular[1], .specular[2] = specular[2], .specular[3] = specular[3]};

	if (num_lights < MAX_LIGHTS)
	{
		lights[num_lights] = new_light;
		glLightfv(num_lights + 0x4000, GL_DIFFUSE, new_light.diffusion);
		glLightfv(num_lights + 0x4000, GL_SPECULAR, new_light.specular);
		glLightfv(num_lights + 0x4000, GL_POSITION, new_light.position);
		glEnable(num_lights + 0x4000);
		num_lights++;
	}
}

void create_spotlight(GLfloat position[4], GLfloat ambient[4], GLfloat diffusion[4], GLfloat specular[4], GLfloat cutoff, GLfloat exponent, GLfloat direction[4])
{
	Light new_light = { .position[0] = position[0],.position[1] = position[1],.position[2] = position[2] + 4.1,.position[3] = position[3],
		.ambient[0] = ambient[0],.ambient[1] = ambient[1],.ambient[2] = ambient[2],.ambient[3] = ambient[3],
		.diffusion[0] = diffusion[0],.diffusion[1] = diffusion[1],.diffusion[2] = diffusion[2],.diffusion[3] = diffusion[3],
		.specular[0] = specular[0],.specular[1] = specular[1],.specular[2] = specular[2],.specular[3] = specular[3] };

	if (num_lights < MAX_LIGHTS)
	{
		lights[num_lights] = new_light;
		glLightfv(num_lights + 0x4000, GL_DIFFUSE, new_light.diffusion);
		glLightfv(num_lights + 0x4000, GL_SPECULAR, new_light.specular);
		glLightfv(num_lights + 0x4000, GL_POSITION, new_light.position);
		glLightf(num_lights + 0x4000, GL_SPOT_CUTOFF, cutoff);
		glLightf(num_lights + 0x4000, GL_SPOT_EXPONENT, exponent);
		glLightfv(num_lights + 0x4000, GL_SPOT_DIRECTION, direction);
		glEnable(num_lights + 0x4000);
		num_lights++;
	}
}

void toggle_lights()
{
	switch (current_lighting_mode)
	{
	case NO_LIGHTS:
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		current_lighting_text = "NO LIGHTS";
		break;
	case ONE_LIGHT:
		glEnable(GL_LIGHT0);
		current_lighting_text = "ONE LIGHT";
		break;
	case TWO_LIGHTS:
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		current_lighting_text = "TWO LIGHTS";
		break;
	case ALL_LIGHTS:
		for (int i = 0; i < num_lights; i++)
		{
			glEnable(i + 0x4000);
		}
		current_lighting_text = "ALL LIGHTS";
		break;
	}

	current_lighting_mode = (current_lighting_mode + 1) % 4;
}

char * get_lighting_mode(void)
{
	return current_lighting_text;
}

void change_intensity(GLfloat delta)
{
	for (int i = 0; i < num_lights; i++)
	{
		if (glIsEnabled(i + 0x4000))
		{
			float attr[4] = {0, 0, 0, 0};

			glGetLightfv(GL_LIGHT0 + i, GL_DIFFUSE, attr);
			if (attr[0] + delta >= 0.0 || attr[1] + delta >= 0.0 || attr[2] + delta >= 0.0)
				attr[0] += delta, attr[1] += delta, attr[2] += delta;
			glLightfv(i + 0x4000, GL_DIFFUSE, attr);

			glGetLightfv(GL_LIGHT0 + i, GL_SPECULAR, attr);
			if (attr[0] + delta >= 0.0 || attr[1] + delta >=0.0 || attr[2] + delta >= 0.0)
				attr[0] += delta, attr[1] += delta, attr[2] += delta;
			glLightfv(i + 0x4000, GL_SPECULAR, attr);
		}
	}
}