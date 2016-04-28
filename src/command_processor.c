/*
*
*/

#include<stdlib.h>
#include<string.h>
#include<GL/glut.h>
#include "main.h"
#include "command_processor.h"
#include "command_prompt.h"
#include "person.h"
#include "camera.h"
#include "buildings.h"
#include "lighting.h"



static Command commands[100];
static int num_commands = 0;

void add_command(char * name, void (*function)(int, char **))
{
	Command command = { "", 0, { "" }, 0 };
	int length = strlen(name);
	strcpy_s(command.name, sizeof command.name, name);
	command.main_function = function;
	commands[num_commands++] = command;
}

void add_sub_command(char * main_command, char * name)
{
	for (int i = 0; i < num_commands; i++)
	{
		if (_stricmp(commands[i].name, main_command) == 0)
		{
			strcpy_s(commands[i].sub_commands[commands[i].num_sub_commands++], 20, name);
			return;
		}
	}
}

void process_command(int num_args, char * args[])
{
	if (num_args > 0)
	{
		for (int i = 0; i < num_commands; i++)
		{
			if (_stricmp(commands[i].name, args[0]) == 0)
			{
				commands[i].main_function(num_args - 1, args);
				return;
			}
		}
		main_commands(0, args);
		/*if (_stricmp(args[0], "toggle") == 0)
		{
			main_commands(num_args, args);
		}
		else if (_stricmp(args[0], "tour") == 0)
		{
			main_commands(num_args, args);
		}
		else if (_stricmp(args[0], "exit") == 0)
		{
			main_commands(num_args, args);
		}
		else if (_stricmp(args[0], "lighting") == 0)
		{
			if (num_args == 1)
			{
				char * help[2] = { "lighting", "help" };
				lighting_commands(num_args, help);
			}
			else
			{
				lighting_commands(num_args - 1, args);
			}
		}
		else if (_stricmp(args[0], "person") == 0)
		{
			if (num_args == 1)
			{
				char * help[2] = { "person", "help" };
				person_commands(num_args, help);
			}
			else
			{
				person_commands(num_args - 1, args);
			}
		}
		else
		{
			main_commands(num_args, args);
		}*/
	}
	else
	{
		args[0] = "help";
		main_commands(num_args, args);
	}
}

int get_num_commands(void)
{
	return num_commands;
}

Command * get_commands(void)
{
	return commands;
}

char * get_sub_commands(char * main_command)
{
	for (int i = 0; i < num_commands; i++)
	{
		if (_stricmp(commands[i].name, main_command) == 0)
		{
			return commands[i].sub_commands;
		}
	}
	return "";
}

int get_num_sub_commands(char * main_command)
{
	for (int i = 0; i < num_commands; i++)
	{
		if (_stricmp(commands[i].name, main_command) == 0)
		{
			return commands[i].num_sub_commands;
		}
	}
	return 0;
}

void print_command(char * str)
{
	write_to_command_history(str);
}