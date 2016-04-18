#pragma once
#ifndef __buildings_h__
#define __buildings_h__

typedef struct Building
{
	GLfloat posX;
	GLfloat posY;
	GLfloat posZ;
	int num_bounds;
	GLfloat bounds[15][6];
} Building;

void draw_buildings(void);
GLfloat * get_ground_size(void);
Building * get_buildings(void);
int get_num_buildings(void);
#endif // !__buildings_h__
