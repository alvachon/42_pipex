/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:23:50 by alvachon          #+#    #+#             */
/*   Updated: 2023/01/18 21:11:51 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*find_path(char *cmd, char *env[])
{
	int		i;
	char	**paths;
	char	*url;
	char	*path;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		url = ft_strjoin(paths[i], "/");
		path = ft_strjoin(url, cmd);
		free(url);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_freeall(paths);
	return (0);
}

void	execute_token(char *av, char *env[])
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(av, ' ');
	path = find_path(cmd[0], env);
	if (!path)
	{
		ft_freeall(cmd);
		error(ERROR_PATH);
	}
	if (execve(path, cmd, env) == -1)
		error(ERROR_EXECVE);
}

void	pipe_out(char **av, int *fds, char *env[])
{
	int	outfile;

	outfile = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (outfile < 0)
		error(NO_FILE);
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	execute_token(av[3], env);
}

void	child_pipe_in(char **av, int *fds, char *env[])
{
	int	infile;

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
		error(NO_FILE);
	close(fds[0]);
	dup2(infile, STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	execute_token(av[2], env);
}

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
		return (0);
	}
	else
		error(ARG_COUNT);
	return (0);
}
