/*
* Name: Chase Counsell
* Project: COMP 5400 Project 4
* File: lighting.c
* Date: 3/17/2016
* Description: Functions for controlling the lighting
*/

#define MAX_LIGHTS 8
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdarg.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<GL/glut.h>
#include "lighting.h"
#include "command_processor.h"

typedef struct Light
{
	GLfloat position[4];
	GLfloat ambient[4];
	GLfloat diffusion[4];
	GLfloat specular[4];
	GLfloat cutoff;
	GLfloat exponent;
	GLfloat direction[3];
}Light;

typedef enum LIGHTING_MODE {NO_LIGHTS, ONE_LIGHT, TWO_LIGHTS, ALL_LIGHTS} LIGHTING_MODE;
LIGHTING_MODE current_lighting_mode = NO_LIGHTS;
char * current_lighting_text = "ALL LIGHTS";

static int is_day = DAY;

static GLfloat no_mat[4] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat default_pos[4] = { 0.0, 0.0, 1.0, 0.0 };
static GLfloat default_am[4] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat default_dif[4] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat default_spec[4] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat default_dir[3] = { 0.0, 0.0, -1.0 };
static GLfloat default_cutoff = 180.0;
static GLfloat default_exp = 0.0;

static Light lights[MAX_LIGHTS];
static int num_lights = 0;
static GLfloat global_ambient[4] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat sun_emission[4] = { 0.3, 0.3, 0.3, 1.0 };

void initialize_lighting(void)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);

	add_command("lighting", &lighting_commands);
	add_sub_command("lighting", "help");
	add_sub_command("lighting", "list");
	add_sub_command("lighting", "create");
	add_sub_command("lighting", "set");
	add_sub_command("lighting", "enable");
	add_sub_command("lighting", "disable");
}

void create_light(int num_args, ...)
{
	if (num_lights < MAX_LIGHTS)
	{
		va_list arguments;
		Light new_light;
		GLfloat * light_pos = default_pos,
			*light_am = default_am,
			*light_dif = default_dif,
			*light_spec = default_spec,
			*light_dir = default_dir;

		va_start(arguments, num_args);
		switch(num_args)
		{
		case 1:
			light_pos = va_arg(arguments, GLfloat *);
			break;
		case 2:
			light_pos = va_arg(arguments, GLfloat *);
			light_am = va_arg(arguments, GLfloat *);
			break;
		case 3:
			light_pos = va_arg(arguments, GLfloat *);
			light_am = va_arg(arguments, GLfloat *);
			light_dif = va_arg(arguments, GLfloat *);
			break;
		case 4:
			light_pos = va_arg(arguments, GLfloat *);
			light_am = va_arg(arguments, GLfloat *);
			light_dif = va_arg(arguments, GLfloat *);
			light_spec = va_arg(arguments, GLfloat *);
			break;
		default:
			break;
		}
		va_end(arguments);

		for (int i = 0; i < 4; i++) new_light.position[i] = light_pos[i];
		for (int i = 0; i < 4; i++) new_light.ambient[i] = light_am[i];
		for (int i = 0; i < 4; i++) new_light.diffusion[i] = light_dif[i];
		for (int i = 0; i < 4; i++) new_light.specular[i] = light_spec[i];
	
		lights[num_lights] = new_light;
		glLightfv(num_lights + 0x4000, GL_DIFFUSE, new_light.diffusion);
		glLightfv(num_lights + 0x4000, GL_SPECULAR, new_light.specular);
		glLightfv(num_lights + 0x4000, GL_POSITION, new_light.position);
		glEnable(num_lights + 0x4000);
		num_lights++;

		print_command("Created light");
	}
	else
	{
		print_command("CANNOT CREATE - Max light count reached");
	}
}

void create_spotlight(int num_args, ...)
{
	if (num_lights < MAX_LIGHTS)
	{
		va_list arguments;
		Light new_light;
		GLfloat * light_pos = default_pos,
				*light_am = default_am,
				*light_dif = default_dif,
				*light_spec = default_spec,
				*light_dir = default_dir;

		GLfloat light_cutoff = default_cutoff,
				light_exp = default_exp;

		va_start(arguments, num_args);
		switch (num_args)
		{
		case 1:
			light_pos = va_arg(arguments, GLfloat *);
			break;
		case 2:
			light_pos = va_arg(arguments, GLfloat *);
			light_am = va_arg(arguments, GLfloat *);
			break;
		case 3:
			light_pos = va_arg(arguments, GLfloat *);
			light_am = va_arg(arguments, GLfloat *);
			light_dif = va_arg(arguments, GLfloat *);
			break;
		case 4:
			light_pos = va_arg(arguments, GLfloat *);
			light_am = va_arg(arguments, GLfloat *);
			light_dif = va_arg(arguments, GLfloat *);
			light_spec = va_arg(arguments, GLfloat *);
			break;
		case 5:
			light_pos = va_arg(arguments, GLfloat *);
			light_am = va_arg(arguments, GLfloat *);
			light_dif = va_arg(arguments, GLfloat *);
			light_spec = va_arg(arguments, GLfloat *);
			light_dir = va_arg(arguments, GLfloat *);
			break;
		case 6:
			light_pos = va_arg(arguments, GLfloat *);
			light_am = va_arg(arguments, GLfloat *);
			light_dif = va_arg(arguments, GLfloat *);
			light_spec = va_arg(arguments, GLfloat *);
			light_dir = va_arg(arguments, GLfloat *);
			light_cutoff = va_arg(arguments, double);
			break;
		case 7:
			light_pos = va_arg(arguments, GLfloat *);
			light_am = va_arg(arguments, GLfloat *);
			light_dif = va_arg(arguments, GLfloat *);
			light_spec = va_arg(arguments, GLfloat *);
			light_dir = va_arg(arguments, GLfloat *);
			light_cutoff = va_arg(arguments, double);
			light_exp = va_arg(arguments, double);
			break;
		default:
			break;
		}
		va_end(arguments);

		for (int i = 0; i < 4; i++) new_light.position[i] = light_pos[i];
		for (int i = 0; i < 4; i++) new_light.ambient[i] = light_am[i];
		for (int i = 0; i < 4; i++) new_light.diffusion[i] = light_dif[i];
		for (int i = 0; i < 4; i++) new_light.specular[i] = light_spec[i];
		new_light.cutoff = light_cutoff;
		new_light.exponent = light_exp;
		for (int i = 0; i < 3; i++) new_light.direction[i] = light_dir[i];

		lights[num_lights] = new_light;
		glLightfv(num_lights + 0x4000, GL_DIFFUSE, new_light.diffusion);
		glLightfv(num_lights + 0x4000, GL_SPECULAR, new_light.specular);
		glLightfv(num_lights + 0x4000, GL_POSITION, new_light.position);
		glLightf(num_lights + 0x4000, GL_SPOT_CUTOFF, light_cutoff);
		glLightf(num_lights + 0x4000, GL_SPOT_EXPONENT, light_exp);
		glLightfv(num_lights + 0x4000, GL_SPOT_DIRECTION, light_dir);
		glEnable(num_lights + 0x4000);
		num_lights++;

		print_command("Created spotlight");
	}
	else
	{
		print_command("CANNOT CREATE - Max light count reached");
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
		if (glIsEnabled(i + 0x4000) && i != 2)
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

void draw_sun_moon(void)
{
	if (is_day == DAY)
		glColor3f(1.0, 0.8, 0.0);
	else
		glColor3f(0.078, 0.235, 0.706);
	glMaterialfv(GL_FRONT, GL_EMISSION, sun_emission);
	glutSolidSphere(5.0, 100, 100);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

void toggle_daylight(void) 
{ 
	is_day = !is_day;
	if (!is_day) glClearColor(0.0, 0.0, 0.0, 1.0);
	if (is_day) glClearColor(0.015, 0.463, 0.851, 1.0);
}

int is_daytime(void) 
{ 
	return is_day; 
}

static void list_lights(void)
{
	char str[100] = "List of lights:";
	print_command("");
	print_command(str); 

	for (int i = 0; i < num_lights; i++)
	{
		sprintf_s(str, 100, "LIGHT %d : ", i);
		if (glIsEnabled(i + 0x4000)) 
			strcat_s(str, 100, "ENABLED");
		else 
			strcat_s(str, 100, "DISABLED");

		print_command(str);
	}
}

static void set_light_position(int light, int num_args, ...)
{
	GLfloat new_position[4] = { 0.0, 0.0, 0.0, 1.0 };

	va_list arguments;
	va_start(arguments, num_args);
	
	switch (num_args)
	{
	case 1:
		new_position[0] = va_arg(arguments, double);
		break;
	case 2:
		new_position[0] = va_arg(arguments, double);
		new_position[1] = va_arg(arguments, double);
		break;
	case 3:
		new_position[0] = va_arg(arguments, double);
		new_position[1] = va_arg(arguments, double);
		new_position[2] = va_arg(arguments, double);
		break;
	default:
		break;
	}
	va_end(arguments);

	glLightfv(light + 0x4000, GL_POSITION, new_position);
	for (int i = 0; i < 3; i++) lights[light].position[i] = new_position[i];

	char str[100];
	sprintf_s(str, sizeof str, "Set position of LIGHT %i to %.0f, %.0f, %.0f", light, new_position[0], new_position[1], new_position[2]);
	print_command(str);
}

static void set_light_ambient(int light, int num_args, ...)
{
	GLfloat new_ambient[4] = { 0.0, 0.0, 0.0, 1.0 };

	va_list arguments;
	va_start(arguments, num_args);

	switch (num_args)
	{
	case 1:
		new_ambient[0] = va_arg(arguments, double);
		break;
	case 2:
		new_ambient[0] = va_arg(arguments, double);
		new_ambient[1] = va_arg(arguments, double);
		break;
	case 3:
		new_ambient[0] = va_arg(arguments, double);
		new_ambient[1] = va_arg(arguments, double);
		new_ambient[2] = va_arg(arguments, double);
		break;
	default:
		break;
	}
	va_end(arguments);

	glLightfv(light + 0x4000, GL_AMBIENT, new_ambient);
	for (int i = 0; i < 3; i++) lights[light].ambient[i] = new_ambient[i];

	char str[100];
	sprintf_s(str, sizeof str, "Set ambient of LIGHT %i to %.0f, %.0f, %.0f", light, new_ambient[0], new_ambient[1], new_ambient[2]);
	print_command(str);
}

static void set_light_diffusion(int light, int num_args, ...)
{
	GLfloat new_diffusion[4] = { 0.0, 0.0, 0.0, 1.0 };

	va_list arguments;
	va_start(arguments, num_args);

	switch (num_args)
	{
	case 1:
		new_diffusion[0] = va_arg(arguments, double);
		break;
	case 2:
		new_diffusion[0] = va_arg(arguments, double);
		new_diffusion[1] = va_arg(arguments, double);
		break;
	case 3:
		new_diffusion[0] = va_arg(arguments, double);
		new_diffusion[1] = va_arg(arguments, double);
		new_diffusion[2] = va_arg(arguments, double);
		break;
	default:
		break;
	}
	va_end(arguments);

	glLightfv(light + 0x4000, GL_DIFFUSE, new_diffusion);
	for (int i = 0; i < 3; i++) lights[light].diffusion[i] = new_diffusion[i];

	char str[100];
	sprintf_s(str, sizeof str, "Set diffusion of LIGHT %i to %.0f, %.0f, %.0f", light, new_diffusion[0], new_diffusion[1], new_diffusion[2]);
	print_command(str);
}

static void set_light_specular(int light, int num_args, ...)
{
	GLfloat new_specular[4] = { 0.0, 0.0, 0.0, 1.0 };

	va_list arguments;
	va_start(arguments, num_args);

	switch (num_args)
	{
	case 1:
		new_specular[0] = va_arg(arguments, double);
		break;
	case 2:
		new_specular[0] = va_arg(arguments, double);
		new_specular[1] = va_arg(arguments, double);
		break;
	case 3:
		new_specular[0] = va_arg(arguments, double);
		new_specular[1] = va_arg(arguments, double);
		new_specular[2] = va_arg(arguments, double);
		break;
	default:
		break;
	}
	va_end(arguments);

	glLightfv(light + 0x4000, GL_SPECULAR, new_specular);
	for (int i = 0; i < 3; i++) lights[light].specular[i] = new_specular[i];

	char str[100];
	sprintf_s(str, sizeof str, "Set position of LIGHT %i to %.0f, %.0f, %.0f", light, new_specular[0], new_specular[1], new_specular[2]);
	print_command(str);
}

static void set_light_cutoff(int light, GLfloat cutoff)
{
	glLightf(light + 0x4000, GL_SPOT_CUTOFF, cutoff);
	lights[light].cutoff = cutoff;

	char str[100];
	sprintf_s(str, sizeof str, "Set cutoff of LIGHT %i to %.0f", light, cutoff);
	print_command(str);
}

static void set_light_exponent(int light, GLfloat exponent)
{
	lights[light].exponent = exponent;
	glLightf(light + 0x4000, GL_SPOT_EXPONENT, lights[light].exponent);

	char str[100];
	sprintf_s(str, sizeof str, "Set exponent of LIGHT %i to %.0f", light, exponent);
	print_command(str);
}

static void set_light_direction(int light, int num_args, ...)
{
	GLfloat new_direction[3] = { 0.0, 0.0, 0.0 };

	va_list arguments;
	va_start(arguments, num_args);

	switch (num_args)
	{
	case 1:
		new_direction[0] = va_arg(arguments, double);
		break;
	case 2:
		new_direction[0] = va_arg(arguments, double);
		new_direction[1] = va_arg(arguments, double);
		break;
	case 3:
		new_direction[0] = va_arg(arguments, double);
		new_direction[1] = va_arg(arguments, double);
		new_direction[2] = va_arg(arguments, double);
		break;
	default:
		break;
	}
	va_end(arguments);

	glLightfv(light + 0x4000, GL_SPOT_DIRECTION, new_direction);
	for (int i = 0; i < 3; i++) lights[light].direction[i] = new_direction[i];

	char str[100];
	sprintf_s(str, 50, "Set direction of LIGHT%i to %.1f, %.1f, %.1f", light, new_direction[0], new_direction[1], new_direction[2]);
	print_command(str);
}

GLfloat * get_light_position(int light)
{
	return lights[light].position;
}

void enable_light(int light)
{
	glEnable(light + 0x4000);
	char str[20] = "";
	sprintf_s(str, 20, "Enabled LIGHT%i", light);
	print_command(str);
}

void disable_light(int light)
{
	glDisable(light + 0x4000);
	char str[20] = "";
	sprintf_s(str, 20, "Disabled LIGHT%i", light);
	print_command(str);
}

void lighting_commands(int num_args, char * args[])
{
	if (num_args > 0)
	{
		if (_stricmp(args[1], "list") == 0)
		{
			list_lights();
		}
		else if (_stricmp(args[1], "create") == 0)
		{
			if (num_args == 2 && _stricmp(args[2], "spotlight") == 0)
			{
				create_spotlight(0);
			}
			else if (num_args == 2 && _stricmp(args[2], "light") == 0)
			{
				create_light(0);
			}
			else
			{
				print_command("");
				print_command("Usage: Creates a new light or spotlight");
				print_command("\"/lighting create {light | spotlight}\"");
			}
		}
		else if (_stricmp(args[1], "set") == 0)
		{
			if (num_args >= 3)
			{
				if (_stricmp(args[2], "position") == 0)
				{
					if (num_args == 4) set_light_position(atoi(args[3]), 1, atof(args[4]));
					else if (num_args == 5) set_light_position(atoi(args[3]), 2, atof(args[4]), atof(args[5]));
					else if (num_args == 6) set_light_position(atoi(args[3]), 3, atof(args[4]), atof(args[5]), atof(args[6]));
					else
					{
						print_command("");
						print_command("Usage: Sets the position of the specified light");
						print_command("\"/lighting set position <light> <x> [y z]\"");
					}
				}
				else if (_stricmp(args[2], "ambient") == 0)
				{
					if (num_args == 4) set_light_ambient(atoi(args[3]), 1, atof(args[4]));
					else if (num_args == 5) set_light_ambient(atoi(args[3]), 2, atof(args[4]), atof(args[5]));
					else if (num_args == 6) set_light_ambient(atoi(args[3]), 3, atof(args[4]), atof(args[5]), atof(args[6]));
					else
					{
						print_command("");
						print_command("Usage: Sets the ambient color of the specified light");
						print_command("\"/lighting set ambient <light> <red> [ggreen blue]\"");
					}
				}
				else if (_stricmp(args[2], "diffusion") == 0)
				{
					if (num_args == 4) set_light_diffusion(atoi(args[3]), 1, atof(args[4]));
					else if (num_args == 5) set_light_diffusion(atoi(args[3]), 2, atof(args[4]), atof(args[5]));
					else if (num_args == 6) set_light_diffusion(atoi(args[3]), 3, atof(args[4]), atof(args[5]), atof(args[6]));
					else
					{
						print_command("");
						print_command("Usage: Sets the diffusion color of the specified light");
						print_command("\"/lighting set diffusion <light> <red> [green blue]\"");
					}
				}
				else if (_stricmp(args[2], "specular") == 0)
				{
					if (num_args == 4) set_light_specular(atoi(args[3]), 1, atof(args[4]));
					else if (num_args == 5) set_light_specular(atoi(args[3]), 2, atof(args[4]), atof(args[5]));
					else if (num_args == 6) set_light_specular(atoi(args[3]), 3, atof(args[4]), atof(args[5]), atof(args[6]));
					else
					{
						print_command("");
						print_command("Usage: Sets the specular color of the specified light");
						print_command("\"/lighting set specular <light> <red> [green blue]\"");
					}
				}
				else if (_stricmp(args[2], "cutoff") == 0)
				{
					if (num_args == 4) set_light_cutoff(atoi(args[3]), atof(args[4]));
					else
					{
						print_command("");
						print_command("Usage: Sets the cutoff angle of the specified light");
						print_command("\"/lighting set cutoff <light> <angle>\"");
					}
				}
				else if (_stricmp(args[2], "exponent") == 0)
				{
					if (num_args == 4) set_light_exponent(atoi(args[3]), atof(args[4]));
					else
					{
						print_command("");
						print_command("Usage: Sets the exponent of the specified light");
						print_command("\"/lighting set exponent <light> <exponent>\"");
					}
				}
				else if (_stricmp(args[2], "direction") == 0)
				{
					if (num_args == 4) set_light_direction(atoi(args[3]), 1, atof(args[4]));
					else if (num_args == 5) set_light_direction(atoi(args[3]), 2, atof(args[4]), atof(args[5]));
					else if (num_args == 6) set_light_direction(atoi(args[3]), 3, atof(args[4]), atof(args[5]), atof(args[6]));
					else
					{
						print_command("");
						print_command("Usage: Sets the direction of the specified light");
						print_command("\"/lighting set direction <light> <x> [y z]\"");
					}
				}
				else
				{
					print_command("");
					print_command("Usage: Sets an attribute of the specified light");
					print_command("\"/lighting set {position | ambient | specular | cutoff | exponent | direction}\"");
				}
			}
			else
			{
				print_command("");
				print_command("Usage: Sets an attribute of the specified light");
				print_command("\"/lighting set {position | ambient | specular | cutoff | exponent | direction}\"");
			}
		}
		else if (_stricmp(args[1], "enable") == 0)
		{
			if (num_args == 2) enable_light(atoi(args[2]));
			else if (num_args < 2 || num_args > 2)
			{
				print_command("");
				print_command("Usage: Enables the specified light");
				print_command("\"/lighting enable <light>\"");
			}
		}
		else if (_stricmp(args[1], "disable") == 0)
		{
			if (num_args == 2) disable_light(atoi(args[2]));
			else if (num_args < 2 || num_args > 2)
			{
				print_command("");
				print_command("Usage: Disables the specified light");
				print_command("\"/lighting disable <light>\"");
			}
		}
		else
		{
			char * sub_commands = get_sub_commands("lighting");
			char str[100] = "/lighting ";
			int str_length = strlen(str);

			print_command("");
			print_command("List of lighting commands:");
			for (int i = 0; i < get_num_sub_commands(args[0]); i++)
			{
				memcpy(str + str_length, sub_commands + (i * 20), 20);
				print_command(str);
			}
		}
	}
	else
	{
		char * sub_commands = get_sub_commands("lighting");
		char str[100] = "/lighting ";
		int str_length = strlen(str);

		print_command("");
		print_command("List of lighting commands:");
		for (int i = 0; i < get_num_sub_commands(args[0]); i++)
		{
			memcpy(str + str_length, sub_commands + (i * 20), 20);
			print_command(str);
		}
	}
}