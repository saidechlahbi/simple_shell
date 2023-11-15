#include "shell.h"

/**
 * expande_variables - expand variables
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expande_variables(data_of_program *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buffer__add(line, data->input_line);
	for (i = 0; line[i]; i++)
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			_long_to_string(errno, expansion, 10);
			buffer__add(line, expansion);
			buffer__add(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			_long_to_string(getpid(), expansion, 10);
			buffer__add(line, expansion);
			buffer__add(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expansion[j - 1] = line[i + j];
			temp = _env_get_key(expansion, data);
			line[i] = '\0', expansion[0] = '\0';
			buffer__add(expansion, line + i + j);
			temp ? buffer__add(line, temp) : 1;
			buffer__add(line, expansion);
		}
	if (!_str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = _str_duplicate(line);
	}
}

/**
 * expande_alias - expans aliases
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expande_alias(data_of_program *data)
{
	int i, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer__add(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';

		temp = _get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer__add(expansion, line + i + j);
			line[i] = '\0';
			buffer__add(line, temp);
			line[_str_length(line)] = '\0';
			buffer__add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = _str_duplicate(line);
	}
}

/**
 * buffer__add - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: nothing, but sets errno.
 */
int buffer__add(char *buffer, char *str_to_add)
{
	int length, i;

	length = _str_length(buffer);
	for (i = 0; str_to_add[i]; i++)
	{
		buffer[length + i] = str_to_add[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}
