#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **_copyenv(void)
{
	char **new_environs;
	size_t size;
	int i;

	for (size = 0; environs[size]; size++)
		;

	new_environs = malloc(sizeof(char *) * (size + 1));
	if (!new_environs)
		return (NULL);

	for (i = 0; environs[i]; i++)
	{
		new_environs[i] = malloc(_strlen(environs[i]) + 1);

		if (!new_environs[i])
		{
			for (i--; i >= 0; i--)
				free(new_environs[i]);
			free(new_environs);
			return (NULL);
		}
		_strcpy(new_environs[i], environs[i]);
	}
	new_environs[i] = NULL;

	return (new_environs);
}

/**
 * free_env - Frees the the environment copy.
 */
void free_env(void)
{
	int i;

	for (i = 0; environs[i]; i++)
		free(environs[i]);
	free(environs);
}

/**
 * _getenv - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_getenv(const char *var)
{
	int i, length;

	length = _strlen(var);
	for (i = 0; environs[i]; i++)
	{
		if (_strncmp(var, environs[i], length) == 0)
			return (&environs[i]);
	}

	return (NULL);
}
