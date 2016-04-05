#pragma once
#ifndef __student_h__
#define __student_h__

void draw_head(void);
void draw_hair(void);
void draw_face(void);

void draw_body(void);

void draw_left_arm(void);
void draw_left_bicep(void);
void draw_left_forearm(void);
void draw_left_hand(void);

void draw_right_arm(void);
void draw_right_bicep(void);
void draw_right_forearm(void);
void draw_right_hand(void);

void draw_left_leg(void);
void draw_left_thigh(void);
void draw_left_calf(void);
void draw_left_foot(void);

void draw_right_leg(void);
void draw_right_thigh(void);
void draw_right_calf(void);
void draw_right_foot(void);

void draw_backpack(void);
void draw_phone(void);

void draw_student(void);
void rotate_student(GLfloat degreeX, GLfloat degreeY);
void translate_student(GLfloat delta);
void scale_student(GLfloat factor);
void rotate_head(GLfloat theta, GLfloat phi);

void reset_student(void);
#endif // !__student_h__
