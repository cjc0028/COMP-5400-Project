#pragma once
#ifndef __student_h__
#define __student_h__

void draw_head(int skin_color);
void draw_hair(void);
void draw_face(void);

void draw_body(int shirt_color);

void draw_left_arm(int shirt_color, int skin_color);
void draw_left_bicep(int shirt_color);
void draw_left_forearm(int shirt_color, int skin_color);
void draw_left_hand(int skin_color);

void draw_right_arm(int shirt_color, int skin_color);
void draw_right_bicep(int shirt_color);
void draw_right_forearm(int shirt_color, int skin_color);
void draw_right_hand(int skin_color);

void draw_left_leg(int pants_color, int shoe_color);
void draw_left_thigh(int shirt_color);
void draw_left_calf(int pants_color, int shoe_color);
void draw_left_foot(int shoe_color);

void draw_right_leg(int pants_color, int shoe_color);
void draw_right_thigh(int pants_color);
void draw_right_calf(int pants_color, int shoe_color);
void draw_right_foot(int shoe_color);

void draw_backpack(void);
void draw_phone(void);

void draw_student(void);
void draw_bystander(void);
void rotate_student(GLfloat degreeX, GLfloat degreeY);
void translate_student(GLfloat delta);
void scale_student(GLfloat factor);
void rotate_head(GLfloat theta, GLfloat phi);

void reset_student(void);
#endif // !__student_h__
