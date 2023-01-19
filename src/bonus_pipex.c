
#include "../include/pipex_bonus.h"

void	pipex(char *av, char *env[])
{
	int			fds[2];
	pid_t		parent;

	if (pipe(fds) == -1)
		error(ERROR_PIPE);
	parent = fork();
	if (parent == -1)
		error(ERROR_PIPE);
	if (parent == 0)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		execute_token(av, env);
	}
	else
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		waitpid(parent, NULL, 0);
	}
}

int	open_selector(char *file, int flag)
{
	int	fd;

	fd = -1;
	if (flag == WRITE_CREATE_APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, RWX);
	else if (flag == WRITE_CREATE_TRUNC)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, RWX);
	else if (flag == READ)
		fd = open(file, O_RDONLY, RWX);
	if (fd == -1)
		error(ERROR_PIPE);
	return (fd);
}

int	bonus(int ac, char **av, char *env[])
{
	int	infile;
	int	outfile;
	int	index_arg;

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0 && ac > 5)
		{
			index_arg = 3;
			outfile = open_selector(av[ac - 1], WRITE_CREATE_APPEND);
			redirect_heredoc(av[2]);
		}
		else
		{
			index_arg = 2;
			infile = open_selector(av[1], READ);
			outfile = open_selector(av[ac - 1], WRITE_CREATE_TRUNC);
			dup2(infile, STDIN_FILENO);
		}
		while (index_arg < ac - 2)
			pipex(av[index_arg++], env);
	}
	else
		error(ARG_COUNT);
	return (0);
}
