#pragma once
#ifndef __commands_h__
#define __commands_h__

#define PROMPT_CLOSE 0
#define PROMPT_OPEN 1

int get_prompt_state(void);
void open_command_prompt(void);
void close_command_prompt(void);
void draw_prompt(void);
void write_to_prompt(unsigned char c);
void move_cursor(int key);
#endif // !__commands_h__