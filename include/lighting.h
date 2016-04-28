#pragma once
#ifndef __lighting_h__
#define __lighting_h__

#define DAY 1
#define NIGHT 0

void initialize_lighting(void);

void create_light(int num_args, ...);
void create_spotlight(int num_args, ...);

void toggle_lights();
char * get_lighting_mode(void);
void change_intensity(GLfloat delta);

void draw_sun_moon(void);
void toggle_daylight(void);
int is_daytime(void);

GLfloat * get_light_position(int light);

void lighting_commands(int num_args, char * args[]);
#endif //!__lighting_h__