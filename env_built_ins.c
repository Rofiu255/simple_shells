#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shellby_env - Prints the current environment.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */
int shellby_env(char **args, char __attribute__((__unused__)) **front)
{
	int i;
	char cn = '\n';

	if (!environs)
		return (-1);

	for (i = 0; environs[i]; i++)
	{
		write(STDOUT_FILENO, environs[i], _strlen(environs[i]));
		write(STDOUT_FILENO, &cn, 1);
	}

	(void)args;
	return (0);
}

/**
 * shellby_setenv - Changes or adds an environmental variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the name of the new or existing PATH variable.
 *              args[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environs, *new_value;
	size_t size;
	int i;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (create_error(args, -1));
	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environs[size]; size++)
		;

	new_environs = malloc(sizeof(char *) * (size + 2));
	if (!new_environs)
	{
		free(new_value);
		return (create_error(args, -1));
	}

	for (i = 0; environs[i]; i++)
		new_environs[i] = environs[i];

	free(environs);
	environs = new_environs;
	environs[i] = new_value;
	environs[i + 1] = NULL;

	return (0);
}

/**
 * shellby_unsetenv - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environs;
	size_t size;
	int i, i2;

	if (!args[0])
		return (create_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environs[size]; size++)
		;

	new_environs = malloc(sizeof(char *) * size);
	if (!new_environs)
		return (create_error(args, -1));

	for (i = 0, i2 = 0; environs[i]; i++)
	{
		if (*env_var == environs[i])
		{
			free(*env_var);
			continue;
		}
		new_environs[i2] = environs[i];
		i2++;
	}
	free(environs);
	environs = new_environs;
	environs[size - 1] = NULL;

	return (0);
}
