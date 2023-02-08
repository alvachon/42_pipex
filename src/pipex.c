/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:23:50 by alvachon          #+#    #+#             */
/*   Updated: 2023/01/24 20:07:09 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/* PIPE OUT :
Part 1 : Attribute a file descriptor (outfile) to open function. 

We gonna force this fd as a standard output and
force the intput entry as the entry pipe (fds[0].

1. close unused gate(fds[1])
2. link entry pipe (fds[0]) as stdin (Formal file descriptor 0) with dup2
3. link outfile fd (result) as stdout with dup2
4. Closing outfile since no change was made to be closed by dup2

Now good info on standard fd 0 and 1 (stdin, stdout) for 
second execution modifier.*/
void	pipe_out(char **av, int *fds, char *env[])
{
	int	outfile;

	outfile = open(av[4], O_TRUNC | O_CREAT | O_RDWR, RWX);
	if (outfile == -1)
		error(NO_FILE);
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execute_token(av[3], env);
}

/* CHILD CREATED, PIPE IN:
Part 1 : Attribute a file descriptor (infile) to open function. 

We gonna force this fd as a standard input and
force the output result in the exit pipe (fds[1]).

1. close unused gate(fds[0])
2. link infile fd as stdin with dup2
3. link exit pipe (fds[1]) as stdout (Formal File descriptor 1) with dup2
4. Closing infile since no change was made to be closed by dup2

Now good info on standard fd 0 and 1 (stdin, stdout)
for the first execution modifier. */
void	child_pipe_in(char **av, int *fds, char *env[])
{
	int	infile;

	infile = open(av[1], O_RDONLY, RWX);
	if (infile == -1)
		error(NO_FILE);
	close(fds[0]);
	dup2(fds[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(infile);
	execute_token(av[2], env);
}

/*
MAIN FILE DESCRIPTOR HANDLER:

All pipe and fork systems are on the same call
to simplify the process handling. 

If parent return (0), we are in the sub-duplicate child processing. 
Waitpid wait the result the first part of the pipeline (children process)
and act like a gate to enter in the second part of the pipe. */
int	main(int ac, char **av, char *env[])
{
	int			fds[2];
	pid_t		parent;

	if (ac == 5)
	{
		if (pipe(fds) == -1)
			error(ERROR_PIPE);
		parent = fork();
		if (parent == -1)
			error(ERROR_PIPE);
		if (parent == 0)
			child_pipe_in(av, fds, env);
		waitpid(parent, NULL, 0);
		pipe_out(av, fds, env);
	}
	else
		error(ARG_COUNT);
	return (0);
}
