#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files*/

/************* MACROS **************/

#include "macros.h" /* for msg help and prompt */

/************* STRUCTURES **************/

/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;


/************* MAIN FUNCTIONS *************/


/*========  shell.c  ========*/

/* Inicialize the struct with the info of the program */
void inicializ__data(data_of_program *data, int arc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void _sisifo(char *prompt, data_of_program *data);

/* Print the prompt in a new line */
void handle__ctrl_c(int opr UNUSED);


/*========  _getline.c  ========*/

/* Read one line of the standar input*/
int __getline(data_of_program *data);

/* split the each line for the logical operators if it exist */
int check_logic_opse(char *array_commands[], int i, char array_operators[]);


/*======== expansions.c ========*/

/* expand variables */
void expande_variables(data_of_program *data);

/* expand aliases */
void expande_alias(data_of_program *data);

/* append the string to the end of the buffer*/
int buffer__add(char *buffer, char *str_to_add);


/*======== str_tok.c ========*/

/* Separate the string in tokens using a designed delimiter */
void _tokenize(data_of_program *data);

/* Creates a pointer to a part of a string */
char *__strtok(char *line, char *delim);


/*======== execute.c ========*/

/* Execute a command with its entire path */
int execute(data_of_program *data);


/*======== builtins_list.c ========*/

/* If match a builtin, executes it */
int builtins__list(data_of_program *data);


/*======== find_in_path.c ========*/

/* Creates an array of the path directories */
char **tokenizer_path(data_of_program *data);

/* Search for program in path */
int find_programme(data_of_program *data);


/************** HELPERS FOR MEMORY MANAGEMENT **************/


/*======== helpers_free.c ========*/

/* Frees the memory for directories */
void _free_array_of_pointers(char **directories);

/* Free the fields needed each loop */
void _free_recurrent_data(data_of_program *data);

/* Free all field of the data */
void _free_all_data(data_of_program *data);


/************** BUILTINS **************/


/*======== builtins_more.c ========*/

/* Close the shell */
int builtin__exit(data_of_program *data);

/* Change the current directory */
int builtin__cd(data_of_program *data);

/* set the work directory */
int _set_work_directory(data_of_program *data, char *new_dir);

/* show help information */
int builtin__help(data_of_program *data);

/* set, unset and show alias */
int builtin__alias(data_of_program *data);


/*======== builtins_env.c ========*/

/* Shows the environment where the shell runs */
int builtin__env(data_of_program *data);

/* create or override a variable of environment */
int _builtin_set_env(data_of_program *data);

/* delete a variable of environment */
int _builtin_unset_env(data_of_program *data);


/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*======== env_management.c ========*/

/* Gets the value of an environment variable */
char *_env_get_key(char *name, data_of_program *data);

/* Overwrite the value of the environment variable */
int _env_set_key(char *key, char *value, data_of_program *data);

/* Remove a key from the environment */
int _env_remove_key(char *key, data_of_program *data);

/* prints the current environ */
void _print_environ(data_of_program *data);


/************** HELPERS FOR PRINTING **************/


/*======== helpers_print.c ========*/

/* Prints a string in the standar output */
int __print(char *string);

/* Prints a string in the standar error */
int __printe(char *string);

/* Prints a string in the standar error */
int __print_error(int errorcode, data_of_program *data);


/************** HELPERS FOR STRINGS MANAGEMENT **************/


/*======== helpers_string.c ========*/

/* Counts the number of characters of a string */
int _str_length(char *string);

/* Duplicates an string */
char *_str_duplicate(char *string);

/* Compares two strings */
int _str_compare(char *string1, char *string2, int number);

/* Concatenates two strings */
char *_str_concat(char *string1, char *string2);

/* Reverse a string */
void _str_reverse(char *string);


/*======== helpers_numbers.c ========*/

/* Cast from int to string */
void _long_to_string(long number, char *string, int base);

/* convert an string in to a number */
int __atoi(char *s);

/* count the coincidences of character in string */
int _count_characters(char *string, char *character);


/*======== alias_management.c ========*/

/* print the list of alias */
int _print_alias(data_of_program *data, char *alias);

/* get the alias name */
char *_get_alias(data_of_program *data, char *alias);

/* set the alias name */
int _set_alias(char *alias_string, data_of_program *data);


#endif /* SHELL_H */

