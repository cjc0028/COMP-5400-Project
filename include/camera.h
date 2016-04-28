#pragma once
#ifndef __camera_h__
#define __camera_h__

void translate_camera(float delta);
void rotate_camera(float phi, float psi);
void elevate_camera(int speed);
void strafe_camera(int speed);

void set_camera_position(GLfloat x, GLfloat y, GLfloat z);

int get_camera_speed(void);
int get_camera_rotation_speed(void);
GLfloat * get_camera_position(void);
GLfloat * get_camera_target(void);
GLfloat * get_camera_up(void);
GLfloat * get_camera_angle(void);
GLfloat * get_camera_bounds(void);

void reset_camera(void);
void calculate_target(void);
#endif // !__camera_h__
