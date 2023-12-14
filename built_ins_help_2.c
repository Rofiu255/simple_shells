#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/**
 * help_env - Displays information on the shellby builtin command 'env'.
 */
void help_env(void)
{
	char *msgs = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, _strlen(msgs));
}

/**
 * help_setenv - Displays information on the shellby builtin command 'setenv'.
 */
void help_setenv(void)
{
	char *msgs = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, _strlen(msgs));
	msgs = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, _strlen(msgs));
	msgs = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msgs));
}

/**
 * help_unsetenv - Displays information on the shellby builtin command
 * 'unsetenv'.
 */
void help_unsetenv(void)
{
	char *msgs = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msgs, _strlen(msgs));
	msgs = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msgs, _strlen(msgs));
	msgs = "message to stderr.\n";
	write(STDOUT_FILENO, msgs, _strlen(msgs));
}
