#pragma once
#ifndef __cube_h__
#define __cube_h__

#define COLOR_SKIN 0
#define COLOR_RED 1
#define COLOR_BROWN 2
#define COLOR_GREEN 3
#define COLOR_BLUE 4
#define COLOR_GRAY 5
#define COLOR_WHITE 6
#define COLOR_ORANGE 7
#define COLOR_BLACK 8
#define COLOR_GRASS 9

#define NUM_COLORS 10

extern const char * color_text[NUM_COLORS];

void square(int r);
void draw_cube(void);
void draw_pyramid(void);
void draw_diamond(void);
void change_color(int x);
void toggle_bounds(void);
int bounds_enabled(void);
#endif // !__cube_h__
