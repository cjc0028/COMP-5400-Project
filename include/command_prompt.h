#pragma once
#ifndef __commands_h__
#define __commands_h__

#define PROMPT_CLOSE 0
#define PROMPT_OPEN 1

int get_prompt_state(void);
void open_command_prompt(void);
void close_command_prompt(void);
void clear_prompt(void);
void clear_history(void);
void draw_prompt(void);
void write_to_prompt(unsigned char c);
void write_to_command_history(char * text);
void move_cursor(int key);
void run_command(void);
#endif // !__commands_h__