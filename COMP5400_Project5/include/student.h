#pragma once
#ifndef __student_h__
#define __student_h__

void draw_student(void);
void draw_bystander(void);
void rotate_student(GLfloat degreeX, GLfloat degreeY);
void translate_student(GLfloat delta);
void scale_student(GLfloat factor);
void rotate_head(GLfloat theta, GLfloat phi);

void reset_student(void);
#endif // !__student_h__
