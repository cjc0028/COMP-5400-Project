#pragma once
#ifndef __lighting_h__
#define __lighting_h__
void initialize_lighting(void);

void create_light(GLfloat position[4], GLfloat ambient[4], GLfloat diffusion[4], GLfloat specular[4]);
void create_spotlight(GLfloat position[4], GLfloat ambient[4], GLfloat diffusion[4], GLfloat specular[4], GLfloat cutoff, GLfloat exponent, GLfloat direction[4]);

void toggle_lights();
char * get_lighting_mode(void);
void change_intensity(GLfloat delta);
#endif //!__lighting_h__