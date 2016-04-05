#pragma once
#ifndef __buildings_h__
#define __buildings_h__

void draw_shelby(GLfloat x, GLfloat z);
void draw_wiggins(GLfloat x, GLfloat z);
void draw_woltosz(GLfloat x, GLfloat z);
void draw_broun(GLfloat x, GLfloat z);
void draw_lbuilding(GLfloat x, GLfloat z);
void draw_shops(GLfloat x, GLfloat z);
void draw_waterplant(GLfloat x, GLfloat z);
void draw_textile(GLfloat x, GLfloat z);
void draw_ramsey(GLfloat x, GLfloat z);
void draw_wilmore(GLfloat x, GLfloat z);
void draw_ross(GLfloat x, GLfloat z);
void draw_harbert(GLfloat x, GLfloat z);
void draw_davis(GLfloat x, GLfloat z);

void draw_buildings(void);
void calculate_bounds(struct Building *building, GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ);
void draw_bounds(void);
#endif // !__buildings_h__
