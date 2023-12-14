#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

void sig_handler(int sig);
int execute(char **args, char **front);

/**
 * sig_handler - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void sig_handler(int sig)
{
	char *new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * execute - Executes a command in a child process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int execute(char **args, char **front)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = get_location(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			rets = (create_error(args, 126));
		else
			rets = (create_error(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
				ret = (create_error(args, 126));
			free_env();
			free_args(args, front);
			free_alias_list(aliases);
			_exit(rets);
		}
		else
		{
			wait(&status);
			rets = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return (rets);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int rets = 0, retns;
	int *exe_rets = &retns;
	char *prompt = "$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, sig_handler);

	*exe_rets = 0;
	environs = _copyenv();
	if (!environs)
		exit(-100);

	if (argc != 1)
	{
		rets = proc_file_commands(argv[1], exe_rets);
		free_env();
		free_alias_list(aliases);
		return (*exe_rets);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (rets != END_OF_FILE && ret != EXIT)
			rets = handle_args(exe_rets);
		free_env();
		free_alias_list(aliases);
		return (*exe_rets);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		rets = handle_args(exe_rets);
		if (rets == END_OF_FILE || rets == EXIT)
		{
			if (rets == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			free_alias_list(aliases);
			exit(*exe_rets);
		}
	}

	free_env();
	free_alias_list(aliases);
	return (*exe_rets);
}
