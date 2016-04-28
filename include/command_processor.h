#pragma once
#ifndef __command_processor_h__
#define __command_processor_h__

typedef struct Command
{
	char name[20];
	void (*main_function)(int, char **);
	char sub_commands[100][20];
	int num_sub_commands;
}Command;

void process_command(int num_args, char * args[]);
void print_command(char * str);
void add_command(char * name, void (*function)(int, char **));
void add_sub_command(char * main_command, char * name);
Command * get_commands(void);
char * get_sub_commands(char * main_command);
int get_num_commands(void);
int get_num_sub_commands(char * main_command);
#endif // !__command_processor_h__