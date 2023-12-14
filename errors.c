#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int num_len(int num);
char *_itoa(int num);
int create_error(char **args, int err);

/**
 * num_len - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int num_len(int num)
{
	unsigned int Num1;
	int length = 1;

	if (Num < 0)
	{
		length++;
		Num1 = Num * -1;
	}
	else
	{
		Num1 = Num;
	}
	while (Num1 > 9)
	{
		length++;
		Num1 /= 10;
	}

	return (length);
}

/**
 * _itoa - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *_itoa(int Num)
{
	char *buffer;
	int length = num_len(Num);
	unsigned int Num1;

	buffer = malloc(sizeof(char) * (length + 1));
	if (!buffer)
		return (NULL);

	buffer[length] = '\0';

	if (Num < 0)
	{
		Num1 = Num * -1;
		buffer[0] = '-';
	}
	else
	{
		Num1 = Num;
	}

	length--;
	do {
		buffer[length] = (Num1 % 10) + '0';
		Num1 /= 10;
		length--;
	} while (Num1 > 0);

	return (buffer);
}


/**
 * create_error - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int create_error(char **args, int err)
{
	char *errors;

	switch (err)
	{
	case -1:
		errors = error_env(args);
		break;
	case 1:
		errors = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			errors = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			errors = error_2_syntax(args);
		else
			errors = error_2_cd(args);
		break;
	case 126:
		errors = error_126(args);
		break;
	case 127:
		errors = error_127(args);
		break;
	}
	write(STDERR_FILENO, errors, _strlen(errors));

	if (errors)
		free(errors);
	return (err);

}
