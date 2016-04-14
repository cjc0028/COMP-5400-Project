#pragma once
#ifndef __person_h__
#define __person_h__

void draw_student(void);
void draw_bystander(void);
void rotate_student(GLfloat phi, GLfloat psi);
void translate_student(GLfloat delta);
void scale_student(GLfloat factor);
void rotate_head(GLfloat phi, GLfloat psi);
GLfloat * get_position(void);
GLfloat * get_angle(void);
void reset_student(void);
#endif // !__person_h__
