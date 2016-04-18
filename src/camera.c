/*
* Name: Chase Counsell
* Project: COMP 5400 Project 4
* File: camera.c
* Date: 3/17/2016
* Description: Functions for controlling the camera
*/

#define _USE_MATH_DEFINES
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

Camera camera1 = { { -100.0, 2.95, 10.0 },
{ -100.0, 2.95, -1.0 },
{ 0.0, 1.0, 0.0 },
{ 0.0, 0.0 },
{ 0.0, 0.0, 0.0, 0.5, 0.5, 0.5} };

Camera initial_camera = { { -100.0, 2.95, 10.0 },
{ -100.0, 2.95, -1.0 },
{ 0.0, 1.0, 0.0 },
{ 0.0, 0.0 },
{ 0.5, -0.5, 0.5, -0.5, 0.5, -0.5 } };

void calculate_target(void)
{
	camera1.target[0] = camera1.position[0] + sin(camera1.angle[0] * M_PI / 180) * cos(camera1.angle[1] * M_PI / 180);
	camera1.target[1] = camera1.position[1] + sin(camera1.angle[1] * M_PI / 180);
	camera1.target[2] = camera1.position[2] - cos(camera1.angle[0] * M_PI / 180) * cos(camera1.angle[1] * M_PI / 180);
}

void translate_camera(float delta)
{
	camera1.position[0] += delta * sin(camera1.angle[0] * M_PI / 180) * cos(camera1.angle[1] * M_PI / 180);
	camera1.position[1] += delta * sin(camera1.angle[1] * M_PI / 180);
	camera1.position[2] += delta * -cos(camera1.angle[0] * M_PI / 180) * cos(camera1.angle[1] * M_PI / 180);
	calculate_target();
}

void rotate_camera(float theta, float phi)
{
	theta = (int)theta % 360;
	phi = (int)phi % 360;

	camera1.angle[0] = (camera1.angle[0] + theta);
	if (abs(camera1.angle[1] + phi) < 90)
		camera1.angle[1] = (camera1.angle[1] + phi);
	calculate_target();
}

GLfloat * get_camera_position(void)
{
	return camera1.position;
}

GLfloat * get_camera_target(void)
{
	return camera1.target;
}

GLfloat * get_camera_up(void)
{
	return camera1.up;
}

GLfloat * get_camera_angle(void)
{
	return camera1.angle;
}

GLfloat * get_camera_bounds(void)
{
	return camera1.bounds;
}

void reset_camera(void)
{
	camera1 = initial_camera;
}