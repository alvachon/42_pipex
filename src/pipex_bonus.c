
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/pipex_bonus.h"

#define ARG_COUNT "Problem with the number of argument.\n"
#define NO_FILE "Problem with presence of file.\n"
#define ERROR_COMMAND "Problem with validity of command.\n"
#define ERROR_PIPE "Problem with the pipe stream (fds[0], fds[1]).\n"
#define ERROR_PATH "Problem with the environ path. \n"
#define ERROR_EXECVE "Problem with execve. \n"
#define HERE_DOC "argument(1) not here_doc \n"

#define WRITE_CREATE_APPEND 1
#define WRITE_CREATE_TRUNC 2
#define READ 3
#define RWX 0777

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*mem;

	mem = b;
	while (len > 0)
	{
		*mem = (unsigned char)c;
		mem++;
		len--;
	}
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	mem = malloc(count * size);
	if (mem == NULL)
		return (NULL);
	ft_memset(mem, '\0', (count * size));
	return (mem);
}

char	*ft_free(char **line)
{
	if (*line != NULL)
		free(*line);
	return (NULL);
}

int	heredoc(char **line)
{
	int		fd;
	int		i;
	char	input;
	char	*buffer;

	fd = read(STDIN_FILENO, &input, STDOUT_FILENO);
	if (fd == -1)
		error(ERROR_PIPE);
	i = 0;
	buffer = ft_calloc(1, 16384);
	while (fd && input != '\n' && input != '\0')
	{
		if (input != '\n' && input != '\0')
				buffer[i] = input;
		i++;
		fd = read(STDIN_FILENO, &input, STDOUT_FILENO);
	}
	buffer[i] = '\n';
	buffer[++i] = '\n';
	*line = buffer;
	free(buffer);
	return (fd);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*ps1;
	unsigned char	*ps2;

	i = 0;
	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (ps1[i] == ps2[i] && ps1[i] != '\0' && ps2[i] != '\0'
		&& i < (n - 1))
		i++;
	return (ps1[i] - ps2[i]);
}

void	redirect_heredoc(char *token, int ac)
{
	int		fds[2];
	pid_t	parent;
	char	*line;

	if (pipe(fds) == -1)
		error(ERROR_PIPE);
	parent = fork();
	if (parent == -1)
		error(ERROR_PIPE);
	if (parent == 0)
	{
		close(fds[0]);
		while (heredoc(&line))
		{
			if (ft_strncmp(line, token, ft_strlen(token)) == 0)
				exit(EXIT_SUCCESS);
			write(fds[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		wait(NULL);
	}
}

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

int	main(int ac, char **av, char *env[])
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
			redirect_heredoc(av[2], ac);
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
