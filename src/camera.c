/*
* Name: Chase Counsell
* Project: COMP 5400 Project 4
* File: camera.c
* Date: 3/17/2016
* Description: Functions for controlling the camera
*/

#define _USE_MATH_DEFINES
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#include "camera.h"

typedef struct Camera
{
	GLfloat position[3];
	GLfloat target[3];
	GLfloat up[3];
	GLfloat angle[2];
	GLfloat bounds[6];
} Camera;

Camera camera = { { -100.0, 2.95, 10.0 },
{ -100.0, 2.95, -1.0 },
{ 0.0, 1.0, 0.0 },
{ 0.0, 0.0 },
{ -100.0, 0.5, 10.0, 0.5, 2.95, 0.5 } };

Camera initial_camera = { { -100.0, 2.95, 10.0 },
{ -100.0, 2.95, -1.0 },
{ 0.0, 1.0, 0.0 },
{ 0.0, 0.0 },
{ -100.0, 0.5, 10.0, 0.5, 2.95, 0.5 } };

void calculate_target(void)
{
	camera.target[0] = camera.position[0] + sin(camera.angle[0] * M_PI / 180) * cos(camera.angle[1] * M_PI / 180);
	camera.target[1] = camera.position[1] + sin(camera.angle[1] * M_PI / 180);
	camera.target[2] = camera.position[2] - cos(camera.angle[0] * M_PI / 180) * cos(camera.angle[1] * M_PI / 180);
}

void translate_camera(float delta)
{
	camera.position[0] += delta * sin(camera.angle[0] * M_PI / 180) * cos(camera.angle[1] * M_PI / 180);
	camera.position[1] += delta * sin(camera.angle[1] * M_PI / 180);
	camera.position[2] += delta * -cos(camera.angle[0] * M_PI / 180) * cos(camera.angle[1] * M_PI / 180);
	calculate_target();

	for (int i = 0; i < 3; i++) camera.bounds[i] = camera.position[i];
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