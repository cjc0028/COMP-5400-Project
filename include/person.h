#pragma once
#ifndef __person_h__
#define __person_h__

typedef struct Body_Part
{
	GLfloat scale[3];
	GLfloat angle[3];
}Body_Part;

typedef struct Person
{
	int is_student;
	int in_air;
	int speed;
	int rotation_speed;
	GLfloat position[4];                                               // X, Y, and Z position
	GLfloat velocity[4];											   // Player velocity
	GLfloat scale;                                                     // Scale used in all directions
	GLfloat angle[3];                                                  // [0] - body tilt, [1] - body rotation
	int colors[4];
	Body_Part body_parts[11];
	GLfloat bounds[6];
} Person;

void initialize_people(void);

void create_student(int num_args, ...);
void create_bystander(int num_args, ...);

void draw_person(int person);
void rotate_person(GLfloat phi, GLfloat psi);
void translate_person(GLfloat delta);
void scale_person(GLfloat factor);
void jump(int person);
void rotate_head(GLfloat phi, GLfloat psi);
void set_person_position(int person, int num_args, ...);
void set_person_angle(int person, int num_args, ...);
void set_person_scale(int person, GLfloat scale);
GLfloat * get_position(void);
Person * get_people(void);
Person get_person(int person);
GLfloat * get_bounds(void);
void select_person(int person);
int get_selected_person(void);
int get_num_people(void);
void reset_person(void);

void person_commands(int num_args, char * args[]);
#endif // !__person_h__
