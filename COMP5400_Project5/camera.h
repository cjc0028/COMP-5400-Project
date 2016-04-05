#pragma once
#ifndef __camera_h__
#define __camera_h__

void translate_camera(float delta);
void rotate_camera(float theta, float phi);

GLfloat * get_camera_position(void);
GLfloat * get_camera_target(void);
GLfloat * get_camera_up(void);
GLfloat * get_camera_angle(void);

void reset_camera(void);
void calculate_target(void);
void camera_mode(void);
#endif // !__camera_h__
