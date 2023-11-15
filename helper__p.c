#include "shell.h"

/**
 * __print - writes a array of chars in the standar output
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int __print(char *string)
{
	return (write(STDOUT_FILENO, string, _str_length(string)));
}
/**
 * __printe - writes a array of chars in the standar error
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int __printe(char *string)
{
	return (write(STDERR_FILENO, string, _str_length(string)));
}

/**
 * __print_error - writes a array of chars in the standart error
 * @data: a pointer to the program's data'
 * @errorcode: error code to print
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int __print_error(int errorcode, data_of_program *data)
{
	char n_as_string[10] = {'\0'};

	_long_to_string((long) data->exec_counter, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		__printe(data->program_name);
		__printe(": ");
		__printe(n_as_string);
		__printe(": ");
		__printe(data->tokens[0]);
		if (errorcode == 2)
			__printe(": Illegal number: ");
		else
			__printe(": can't cd to ");
		__printe(data->tokens[1]);
		__printe("\n");
	}
	else if (errorcode == 127)
	{
		__printe(data->program_name);
		__printe(": ");
		__printe(n_as_string);
		__printe(": ");
		__printe(data->command_name);
		__printe(": not found\n");
	}
	else if (errorcode == 126)
	{
		__printe(data->program_name);
		__printe(": ");
		__printe(n_as_string);
		__printe(": ");
		__printe(data->command_name);
		__printe(": Permission denied\n");
	}
	return (0);
}
