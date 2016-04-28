/*
* Name: Chase Counsell
* Project: COMP 5400 Project 4
* File: camera.c
* Date: 3/17/2016
* Description: Functions for controlling the camera
*/

#define _USE_MATH_DEFINES
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
#include "camera.h"
#include "command_processor.h"

typedef struct Camera
{
	int speed;
	int rotation_speed;
	GLfloat position[3];
	GLfloat target[3];
	GLfloat up[3];
	GLfloat angle[2];
	GLfloat bounds[6];
} Camera;

Camera camera = { 1.0, 2.0, 
{ -100.0, 2.95, 10.0 },
{ -100.0, 2.95, -1.0 },
{ 0.0, 1.0, 0.0 },
{ 0.0, 0.0 },
{ -100.0, 0.5, 10.0, 0.5, 2.95, 0.5 } };

Camera initial_camera = { 1.0, 2.0,
{ -100.0, 2.95, 10.0 },
{ -100.0, 2.95, -1.0 },
{ 0.0, 1.0, 0.0 },
{ 0.0, 0.0 },
{ -100.0, 0.5, 10.0, 0.5, 2.95, 0.5 } };

void initialize_camera()
{
	add_command("camera", &camera_commands);
	add_sub_command("camera", "set");
}

void calculate_target(void)
{
	camera.target[0] = camera.position[0] + sin(camera.angle[0] * M_PI / 180) * cos(camera.angle[1] * M_PI / 180);
	camera.target[1] = camera.position[1] + sin(camera.angle[1] * M_PI / 180);
	camera.target[2] = camera.position[2] - cos(camera.angle[0] * M_PI / 180) * cos(camera.angle[1] * M_PI / 180);
}

void translate_camera(float speed)
{
	camera.position[0] += speed * sin(camera.angle[0] * M_PI / 180) * cos(camera.angle[1] * M_PI / 180);
	camera.position[1] += speed * sin(camera.angle[1] * M_PI / 180);
	camera.position[2] += speed * -cos(camera.angle[0] * M_PI / 180) * cos(camera.angle[1] * M_PI / 180);
	calculate_target();

	camera.bounds[0] = camera.position[0];
	camera.bounds[2] = camera.position[2];
	camera.bounds[4] = camera.position[1];
}

void rotate_camera(float theta, float phi)
{
	theta = (int)theta % 360;
	phi = (int)phi % 360;

	camera.angle[0] = (camera.angle[0] + theta);
	if (abs(camera.angle[1] + phi) < 90)
		camera.angle[1] = (camera.angle[1] + phi);
	calculate_target();
}

void elevate_camera(int speed)
{
	camera.position[1] += speed;
	camera.bounds[4] = camera.position[1];

	calculate_target();
}

void strafe_camera(int speed)
{
	camera.position[0] += speed  * cos(camera.angle[0] * M_PI / 180);
	camera.position[2] += speed  * sin(camera.angle[0] * M_PI / 180);
	calculate_target();

	camera.bounds[0] = camera.position[0];
	camera.bounds[2] = camera.position[2];
}

void set_camera_position(int num_args, ...)
{
	va_list arguments;
	va_start(arguments, num_args);
	
	switch (num_args)
	{
	case 1:
		camera.position[0] = va_arg(arguments, double);
		break;
	case 2:
		camera.position[0] = va_arg(arguments, double);
		camera.position[1] = va_arg(arguments, double);
		break;
	case 3:
		camera.position[0] = va_arg(arguments, double);
		camera.position[1] = va_arg(arguments, double);
		camera.position[2] = va_arg(arguments, double);
		break;
	default:
		break;
	}

	char str[100];
	sprintf_s(str, sizeof str, "Set position of the camera to %.1f, %.1f, %.1f", camera.position[0], camera.position[1], camera.position[2]);
	print_command(str);
}

void set_camera_speed(int speed)
{
	camera.speed = speed;

	char str[100];
	sprintf_s(str, sizeof str, "Set speed of the camera to %i", camera.speed);
	print_command(str);
}

void set_camera_target(int num_args, ...)
{
	va_list arguments;
	va_start(arguments, num_args);

	switch (num_args)
	{
	case 1:
		camera.target[0] = va_arg(arguments, double);
		break;
	case 2:
		camera.target[0] = va_arg(arguments, double);
		camera.target[1] = va_arg(arguments, double);
		break;
	case 3:
		camera.target[0] = va_arg(arguments, double);
		camera.target[1] = va_arg(arguments, double);
		camera.target[2] = va_arg(arguments, double);
		break;
	default:
		break;
	}

	char str[100];
	sprintf_s(str, sizeof str, "Set target of the camera to %.1f, %.1f, %.1f", camera.target[0], camera.target[1], camera.target[2]);
	print_command(str);
}

void set_camera_angle(int num_args, ...)
{
	va_list arguments;
	va_start(arguments, num_args);

	switch (num_args)
	{
	case 1:
		camera.angle[0] = va_arg(arguments, double);
		break;
	case 2:
		camera.angle[0] = va_arg(arguments, double);
		camera.angle[1] = va_arg(arguments, double);
		break;
	default:
		break;
	}

	char str[100];
	sprintf_s(str, sizeof str, "Set angle of the camera to %.1f on the y axis, %.1f on the x axis", camera.position[0], camera.position[1]);
	print_command(str);
}

int get_camera_speed(void)
{
	return camera.speed;
}

int get_camera_rotation_speed(void)
{
	return camera.rotation_speed;
}

GLfloat * get_camera_position(void)
{
	return camera.position;
}

GLfloat * get_camera_target(void)
{
	return camera.target;
}

GLfloat * get_camera_up(void)
{
	return camera.up;
}

GLfloat * get_camera_angle(void)
{
	return camera.angle;
}

GLfloat * get_camera_bounds(void)
{
	return camera.bounds;
}

void reset_camera(void)
{
	camera = initial_camera;
}

void camera_commands(int num_args, char * args[])
{
	if (num_args > 0)
	{
		if (_stricmp(args[1], "set") == 0)
		{
			if (num_args >= 2)
			{
				if (_stricmp(args[2], "position") == 0)
				{
					if (num_args == 3) set_camera_position(1, atof(args[3]));
					else if (num_args == 4) set_camera_position(2, atof(args[3]), atof(args[4]));
					else if (num_args == 5) set_camera_position(3, atof(args[3]), atof(args[4]), atof(args[5]));
					else
					{
						print_command("");
						print_command("Usage: Sets the position of the camera");
						print_command("\"/camera set position <x> [y z]\"");
					}
				}
				else if (_stricmp(args[2], "target") == 0)
				{
					if (num_args == 3) set_camera_target(1, atof(args[3]));
					else if (num_args == 4) set_camera_target(2, atof(args[3]), atof(args[4]));
					else if (num_args == 5) set_camera_target(3, atof(args[3]), atof(args[4]), atof(args[5]));
					else
					{
						print_command("");
						print_command("Usage: Sets the target of the camera");
						print_command("\"/camera set target <x> [y z]\"");
					}
				}
				else if (_stricmp(args[2], "speed") == 0)
				{
					if (num_args == 3) set_camera_speed(atoi(args[3]));
					else
					{
						print_command("");
						print_command("Usage: Sets the speed of the camera");
						print_command("\"/camera set speed <speed>\"");
					}
				}
				else if (_stricmp(args[2], "angle") == 0)
				{
					if (num_args == 3) set_camera_target(1, atof(args[3]));
					else if (num_args == 4) set_camera_target(2, atof(args[3]), atof(args[4]));
					else
					{
						print_command("");
						print_command("Usage: Sets the angle of the camera");
						print_command("\"/camera set target <y> [x]\"");
					}
				}
				else
				{
					print_command("");
					print_command("Usage: Sets an attribute of the camera");
					print_command("\"/camera set {position | target | speed | angle}\"");
				}
			}
			else
			{
				print_command("");
				print_command("Usage: Sets an attribute of the camera");
				print_command("\"/camera set {position | target | speed | angle}\"");
			}
		}
		else
		{
			char * sub_commands = get_sub_commands("camera");
			char str[100] = "/camera ";
			int str_length = strlen(str);

			print_command("");
			print_command("List of camera commands:");
			for (int i = 0; i < get_num_sub_commands(args[0]); i++)
			{
				memcpy(str + str_length, sub_commands + (i * 20), 20);
				print_command(str);
			}
		}
	}
	else
	{
		char * sub_commands = get_sub_commands("camera");
		char str[100] = "/camera ";
		int str_length = strlen(str);

		print_command("");
		print_command("List of camera commands:");
		for (int i = 0; i < get_num_sub_commands(args[0]); i++)
		{
			memcpy(str + str_length, sub_commands + (i * 20), 20);
			print_command(str);
		}
	}
}