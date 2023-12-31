#include "shell.h"

/**
 * _free_recurrent_data - free the fields needed each loop
 * @data: struct of the program's data
 * Return: Nothing
 */
void _free_recurrent_data(data_of_program *data)
{
	if (data->tokens)
		_free_array_of_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * _free_all_data - free all field of the data
 * @data: struct of the program's data
 * Return: Nothing
 */
void _free_all_data(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	_free_recurrent_data(data);
	_free_array_of_pointers(data->env);
	_free_array_of_pointers(data->alias_list);
}

/**
 * _free_array_of_pointers - frees each pointer of an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: nothing
 */
void _free_array_of_pointers(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}
