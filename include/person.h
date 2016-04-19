#pragma once
#ifndef __person_h__
#define __person_h__

typedef struct Person
{
	int is_student;
	GLfloat position[4];                                               // X, Y, and Z position
	GLfloat scale;                                                     // Scale used in all directions
	GLfloat angle[3];                                                  // [0] - body tilt, [1] - body rotation
	GLfloat head_angle[3];
	int colors[4];
} Person;

void create_student(int skin_color, int shirt_color, int pants_color, int shoe_color);
void create_bystander(int skin_color, int shirt_color, int pants_color, int shoe_color);

void draw_person(void);
void rotate_person(GLfloat phi, GLfloat psi);
void translate_person(GLfloat delta);
void scale_person(GLfloat factor);
void rotate_head(GLfloat phi, GLfloat psi);
GLfloat * get_position(void);
Person * get_people(void);
void select_person(int person);
int get_selected_person(void);
int get_num_people(void);
void reset_person(void);
#endif // !__person_h__
