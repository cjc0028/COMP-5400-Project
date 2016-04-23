/*
* Name: Chase Counsell
* Project: COMP 5400 Project 4
* File: collision.c
* Date: 3/17/2016
* Description: Functions for handling collisions
*/

#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include "buildings.h"
#include "collisions.h"

int collision_detected(GLfloat * bounds)
{
	int collision_x = 0, collision_y = 0, collision_z = 0;
	int num_buildings = get_num_buildings();
	Building * building = get_buildings();
	for (int i = 0; i < num_buildings; i++)
	{
		for (int j = 0; j < building->num_bounds; j++)
		{
			collision_x = (fabs(bounds[0] - building->bounds[j][0]) < bounds[1] + building->bounds[j][1]);
			collision_y = (fabs(bounds[4] - building->bounds[j][4]) < bounds[5] + building->bounds[j][5]);
			collision_z = (fabs(bounds[2] - building->bounds[j][2]) < bounds[3] + building->bounds[j][3]);
			
			if (collision_x && collision_y && collision_z) return 1;
		}
		building++;
	}

	return 0;
}