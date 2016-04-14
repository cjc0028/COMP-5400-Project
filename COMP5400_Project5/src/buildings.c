/*
*
*/

#include<GL\glut.h>
#include "buildings.h"
#include "cube.h"

typedef struct Building
{
	GLfloat posX;
	GLfloat posY;
	GLfloat posZ;
	GLfloat right;
	GLfloat left;
	GLfloat front;
	GLfloat rear;
	GLfloat top;
	GLfloat bottom;
} Building;

void calculate_bounds(Building *building, GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ);
void draw_bounds(void);

Building buildings[13];

GLfloat ground_w = 850, ground_d = 450;
GLfloat ground_size[4];


void draw_shelby(GLfloat x, GLfloat z)
{
	Building shelby = {x, 15.0, z, x, x, z, z, 15.0, 15.0};
	GLfloat deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0,
			scaleX = 1.0, scaleY = 30.0, scaleZ = 1.0;

	glPushMatrix();
	change_color(COLOR_ORANGE);
	glTranslatef(x, 15.0, z);

	/* Center Building */
	glPushMatrix();
	glScalef(scaleX = 46.0, scaleY, scaleZ = 30.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&shelby, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glScalef(scaleX = 42.0, scaleY, scaleZ = 42.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&shelby, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glScalef(scaleX = 30.0, scaleY, scaleZ = 50.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&shelby, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	/* Tunnels */
	glPushMatrix();
	glTranslatef(deltaX = -27.0, deltaY = 7.0, deltaZ = 0.0);
	glScalef(scaleX = 8.0, scaleY = 16.0, scaleZ = 8.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&shelby, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 27.0, deltaY = 7.0, deltaZ = 0.0);
	glScalef(scaleX = 8.0, scaleY = 16.0, scaleZ = 8.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&shelby, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	/* Left L Building */
	glPushMatrix();
	glTranslatef(deltaX = -69.5, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 79.0, scaleY = 30.0, scaleZ = 30.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&shelby, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = -40.5, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 15.0, scaleY = 30.0, scaleZ = 34.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&shelby, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = -93.0, deltaY = 0.0, deltaZ = 30.0);
	glScalef(scaleX = 30.0, scaleY = 30.0, scaleZ = 94.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&shelby, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = -93.0, deltaY = 0.0, deltaZ = 67.0);
	glScalef(scaleX = 34.0, scaleY = 30.0, scaleZ = 15.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&shelby, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	/* Right L Building */
	glPushMatrix();
	glTranslatef(deltaX = 69.5, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 79.0, scaleY = 30.0, scaleZ = 30.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&shelby, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 40.5, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 15.0, scaleY = 30.0, scaleZ = 34.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&shelby, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 93.0, deltaY = 0.0, deltaZ = 30.0);
	glScalef(scaleX = 30.0, scaleY = 30.0, scaleZ = 94.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&shelby, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 93.0, deltaY = 0.0, deltaZ = 67.0);
	glScalef(scaleX = 34.0, scaleY = 30.0, scaleZ = 15.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&shelby, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	buildings[0] = shelby;
	glPopMatrix();
}

void draw_wiggins(GLfloat x, GLfloat z)
{
	Building wiggins = { x, 15.0, z, x, x, z, z, 15.0, 15.0 };
	GLfloat deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0,
		scaleX = 1.0, scaleY = 30.0, scaleZ = 1.0;

	glPushMatrix();
	change_color(COLOR_ORANGE);
	glTranslatef(x, 15.0, z);

	glPushMatrix();
	glTranslatef(deltaX = -29.5, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 15.0, scaleY, scaleZ = 50.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&wiggins, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 44.0, scaleY, scaleZ = 48.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&wiggins, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 29.5, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 15.0, scaleY, scaleZ = 50.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&wiggins, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 35.0);
	glScalef(scaleX = 40.0, scaleY, scaleZ = 20.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&wiggins, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	buildings[1] = wiggins;
	glPopMatrix();
}

void draw_woltosz(GLfloat x, GLfloat z)
{
	Building woltosz = { x, 15.0, z, x, x, z, z, 15.0, 15.0 };
	GLfloat deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0,
		scaleX = 1.0, scaleY = 30.0, scaleZ = 1.0;

	glPushMatrix();
	change_color(COLOR_ORANGE);
	glTranslatef(x, 15.0, z);

	glPushMatrix();
	glTranslatef(deltaX = -30.5, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 15.0, scaleY, scaleZ = 50.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&woltosz, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 46.0, scaleY, scaleZ = 44.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&woltosz, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 30.5, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 15.0, scaleY, scaleZ = 52.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&woltosz, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 27.0);
	glScalef(scaleX = 36.0, scaleY, scaleZ = 10.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&woltosz, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	buildings[2] = woltosz;
	glPopMatrix();
}

void draw_broun(GLfloat x, GLfloat z)
{
	Building broun = { x, 15.0, z, x, x, z, z, 15.0, 15.0 };
	GLfloat deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0,
		scaleX = 1.0, scaleY = 30.0, scaleZ = 1.0;

	glPushMatrix();
	change_color(COLOR_ORANGE);
	glTranslatef(x, 15.0, z);

	glPushMatrix();
	glTranslatef(deltaX = -30.0, deltaY = 0.0, deltaZ = 20.0);
	glScalef(scaleX = 45.0, scaleY, scaleZ = 40.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&broun, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 74.0, scaleY, scaleZ = 55.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&broun, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 16.0, deltaY = 0.0, deltaZ = 40.0);
	glScalef(scaleX = 40.0, scaleY, scaleZ = 30.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&broun, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	buildings[3] = broun;
	glPopMatrix();
}

void draw_lbuilding(GLfloat x, GLfloat z)
{
	Building lbuilding = { x, 15.0, z, x, x, z, z, 15.0, 15.0 };
	GLfloat deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0,
		scaleX = 1.0, scaleY = 30.0, scaleZ = 1.0;

	glPushMatrix();
	change_color(COLOR_ORANGE);
	glTranslatef(x, 15.0, z);

	glPushMatrix();
	glTranslatef(deltaX = -120.0, deltaY = 0.0, deltaZ = 2.5);
	glScalef(scaleX = 10.0, scaleY, scaleZ = 25.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&lbuilding, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = -55.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 130.0, scaleY, scaleZ = 20.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&lbuilding, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = -27.5);
	glScalef(scaleX = 20.0, scaleY, scaleZ = 35.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&lbuilding, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = -2.5, deltaY = 0.0, deltaZ = -60.0);
	glScalef(scaleX = 25.0, scaleY, scaleZ = 30.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&lbuilding, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	buildings[4] = lbuilding;
	glPopMatrix();
}

void draw_shops(GLfloat x, GLfloat z)
{
	Building shops = { x, 15.0, z, x, x, z, z, 15.0, 15.0 };
	GLfloat deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0,
		scaleX = 1.0, scaleY = 30.0, scaleZ = 1.0;

	glPushMatrix();
	change_color(COLOR_ORANGE);
	glTranslatef(x, 15.0, z);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 60.0, scaleY, scaleZ = 25.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&shops, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = -37.5);
	glScalef(scaleX = 60.0, scaleY, scaleZ = 30.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&shops, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 37.5);
	glScalef(scaleX = 60.0, scaleY, scaleZ = 30.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&shops, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 25.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 10.0, scaleY, scaleZ = 105.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&shops, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	buildings[5] = shops;
	glPopMatrix();
}

void draw_waterplant(GLfloat x, GLfloat z)
{
	Building waterplant = { x, 15.0, z, x, x, z, z, 15.0, 15.0 };
	GLfloat deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0,
		scaleX = 1.0, scaleY = 30.0, scaleZ = 1.0;

	glPushMatrix();
	change_color(COLOR_ORANGE);
	glTranslatef(x, 15.0, z);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 20.0, scaleY, scaleZ = 60.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&waterplant, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	buildings[6] = waterplant;
	glPopMatrix();
}

void draw_textile(GLfloat x, GLfloat z)
{
	Building textile = { x, 15.0, z, x, x, z, z, 15.0, 15.0 };
	GLfloat deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0,
		scaleX = 1.0, scaleY = 30.0, scaleZ = 1.0;

	glPushMatrix();
	change_color(COLOR_ORANGE);
	glTranslatef(x, 15.0, z);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 130.0, scaleY, scaleZ = 25.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&textile, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 15.0);
	glScalef(scaleX = 10.0, scaleY, scaleZ = 8.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&textile, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	buildings[7] = textile;
	glPopMatrix();
}

void draw_ramsey(GLfloat x, GLfloat z)
{
	Building ramsey = { x, 15.0, z, x, x, z, z, 15.0, 15.0 };
	GLfloat deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0,
		scaleX = 1.0, scaleY = 30.0, scaleZ = 1.0;

	glPushMatrix();
	change_color(COLOR_ORANGE);
	glTranslatef(x, 15.0, z);

	glPushMatrix();
	glTranslatef(deltaX = -45.0, deltaY = 0.0, deltaZ = 4.0);
	glScalef(scaleX = 15.0, scaleY, scaleZ = 33.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&ramsey, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 75.0, scaleY, scaleZ = 22.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&ramsey, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 45.0, deltaY = 0.0, deltaZ = 4.0);
	glScalef(scaleX = 15.0, scaleY, scaleZ = 33.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&ramsey, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	buildings[8] = ramsey;
	glPopMatrix();
}

void draw_wilmore(GLfloat x, GLfloat z)
{
	Building wilmore = { x, 15.0, z, x, x, z, z, 15.0, 15.0 };
	GLfloat deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0,
		scaleX = 1.0, scaleY = 30.0, scaleZ = 1.0;

	glPushMatrix();
	change_color(COLOR_ORANGE);
	glTranslatef(x, 15.0, z);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 115.0, scaleY, scaleZ = 80.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&wilmore, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 85.0, scaleY, scaleZ = 96.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&wilmore, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 11.0, scaleY, scaleZ = 98.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&wilmore, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	buildings[9] = wilmore;
	glPopMatrix();
}

void draw_ross(GLfloat x, GLfloat z)
{
	Building ross = { x, 15.0, z, x, x, z, z, 15.0, 15.0 };
	GLfloat deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0,
		scaleX = 1.0, scaleY = 30.0, scaleZ = 1.0;

	glPushMatrix();
	change_color(COLOR_ORANGE);
	glTranslatef(x, 15.0, z);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 75.0, scaleY, scaleZ = 40.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&ross, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 21.0, scaleY, scaleZ = 52.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&ross, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 65.0, scaleY, scaleZ = 44.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&ross, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	buildings[10] = ross;
	glPopMatrix();
}

void draw_harbert(GLfloat x, GLfloat z)
{
	Building harbert = { x, 15.0, z, x, x, z, z, 15.0, 15.0 };
	GLfloat deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0,
		scaleX = 1.0, scaleY = 30.0, scaleZ = 1.0;

	glPushMatrix();
	change_color(COLOR_ORANGE);
	glTranslatef(x, 15.0, z);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 95.0, scaleY, scaleZ = 36.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&harbert, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = -40.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 15.0, scaleY, scaleZ = 40.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&harbert, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 10.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 15.0, scaleY, scaleZ = 40.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&harbert, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 40.0, deltaY = 0.0, deltaZ = 1.0);
	glScalef(scaleX = 15.0, scaleY, scaleZ = 40.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&harbert, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	buildings[11] = harbert;
	glPopMatrix();
}

void draw_davis(GLfloat x, GLfloat z)
{
	Building davis = { x, 15.0, z, x, x, z, z, 15.0, 15.0 };
	GLfloat deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0,
		scaleX = 1.0, scaleY = 30.0, scaleZ = 1.0;

	glPushMatrix();
	change_color(COLOR_ORANGE);
	glTranslatef(x, 15.0, z);

	glPushMatrix();
	glTranslatef(deltaX = -14.0, deltaY = 0.0, deltaZ = 40.0);
	glScalef(scaleX = 25.0, scaleY, scaleZ = 30.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&davis, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	glPushMatrix();
	glTranslatef(deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0);
	glScalef(scaleX = 40.0, scaleY, scaleZ = 100.0);
	draw_cube();
	glPopMatrix();
	calculate_bounds(&davis, deltaX, deltaY, deltaZ, scaleX, scaleY, scaleZ);

	buildings[12] = davis;
	glPopMatrix();
}

void draw_ground(void)
{
	GLfloat color_grass[3] = { 0.0, 0.7, 0.0 };
	glPushMatrix();
	glColor3fv(color_grass);

	glNormal3f(0.0, 1.0, 0.0);

	for (int x = -ground_w/2; x < ground_w/2; x += 5)
	{
		for (int z = -ground_d/2; z < ground_d/2; z += 5)
		{
			glBegin(GL_QUADS);
			glVertex3f(x, 0, z);
			glVertex3f(x, 0, z + 5);
			glVertex3f(x + 5, 0, z + 5);
			glVertex3f(x + 5, 0, z);
			glEnd();
		}
	}

	glPopMatrix();
}

GLfloat * get_ground_size()
{
	GLfloat ground_size[4] = {-ground_w/2, ground_w/2, -ground_d/2, ground_d/2};
	return ground_size;
}

void draw_buildings(void)
{
	draw_ground();
	draw_shelby(-275.0, -125.0);
	draw_wiggins(-345.0, 15.0);
	draw_woltosz(-205.0, 15.0);
	draw_broun(-165.0, 95.0);
	draw_lbuilding(75.0, 45.0);
	draw_shops(10.0, -45.0);
	draw_waterplant(75.0, -85.0);
	draw_textile(20.0, -145.0);
	draw_ramsey(185.0, -145.0);
	draw_wilmore(185.0, -45.0);
	draw_ross(255.0, 75.0);
	draw_harbert(325.0, -150.0);
	draw_davis(365.0, -55.0);

	if (bounds_enabled()) draw_bounds();
}

void calculate_bounds(Building *building, GLfloat deltaX, GLfloat deltaY, GLfloat deltaZ, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ)
{
	GLfloat newRight = building->posX + deltaX + (scaleX / 2.0);
	GLfloat newLeft = building->posX + deltaX - (scaleX / 2.0);
	GLfloat newFront = building->posZ + deltaZ + (scaleZ / 2.0);
	GLfloat newRear = building->posZ + deltaZ - (scaleZ / 2.0);
	GLfloat newTop = building->posY + deltaY + (scaleY / 2.0);
	GLfloat newBottom = building->posY + deltaY - (scaleY / 2.0);

	if (building->right < newRight) building->right = newRight;
	if (building->left > newLeft) building->left = newLeft;
	if (building->front < newFront) building->front = newFront;
	if (building->rear > newRear) building->rear = newRear;
	if (building->top < newTop) building->top = newTop;
	if (building->bottom > newBottom) building->bottom = newBottom;

}

void draw_bounds(void)
{
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(1.0);

	for (int i = 0; i < 13; i++)
	{
		glBegin(GL_LINE_LOOP);
			glVertex3f(buildings[i].left, buildings[i].bottom, buildings[i].front);
			glVertex3f(buildings[i].right, buildings[i].bottom, buildings[i].front);
			glVertex3f(buildings[i].right, buildings[i].top, buildings[i].front);
			glVertex3f(buildings[i].left, buildings[i].top, buildings[i].front);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(buildings[i].right, buildings[i].top, buildings[i].front);
			glVertex3f(buildings[i].right, buildings[i].bottom, buildings[i].front);
			glVertex3f(buildings[i].right, buildings[i].bottom, buildings[i].rear);
			glVertex3f(buildings[i].right, buildings[i].top, buildings[i].rear);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(buildings[i].right, buildings[i].top, buildings[i].rear);
			glVertex3f(buildings[i].left, buildings[i].top, buildings[i].rear);
			glVertex3f(buildings[i].left, buildings[i].bottom, buildings[i].rear);
			glVertex3f(buildings[i].right, buildings[i].bottom, buildings[i].rear);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(buildings[i].left, buildings[i].bottom, buildings[i].rear);
			glVertex3f(buildings[i].left, buildings[i].bottom, buildings[i].front);
			glVertex3f(buildings[i].left, buildings[i].top, buildings[i].front);
			glVertex3f(buildings[i].left, buildings[i].top, buildings[i].rear);
		glEnd();
	}
	
	glPopMatrix();
}
