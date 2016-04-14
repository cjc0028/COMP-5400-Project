#pragma once
#ifndef __buildings_h__
#define __buildings_h__

void draw_buildings(void);
void calculate_bounds(struct Building *building, GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ);
void draw_bounds(void);
GLfloat * get_ground_size(void);
#endif // !__buildings_h__
