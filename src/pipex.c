/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:23:50 by alvachon          #+#    #+#             */
/*   Updated: 2023/01/10 16:06:52 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
PROGRAM : 
AC 1 & 4: FILE
FILE : Voir les specs . . .
AC 2 & 3 : CMD
CMD : Voir les specs . . .

* < file1 cmd 1 | cmd2 > file2
* ./pipex file1 cmd1 cmd2 file2

* < infile grep a1 | wc -w > outfile
* ./pipex infile "ls -l" "wc -1" outfile

* handle multiple pipe
* here_doc = and

*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/pipex.h"

#define ARG_COUNT "Problem with the number of argument.\n"
#define NO_FILE "Problem with presence of file.\n"
#define ERROR_COMMAND "Problem with validity of command.\n"
#define ERROR_PIPE "Problem with the pipe stream (fds[0], fds[1]).\n"
#define ERROR_PATH "Problem with the environ path. \n"
#define ERROR_EXECVE "Problem with execve. \n"

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

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	len;
	char	*copy;

	i = 0;
	len = ft_strlen(str);
	copy = (char *)malloc(sizeof(char) * len + 1);
	if (copy == NULL)
		return (NULL);
	while (i < len)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	**ft_freeall(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char	*ft_strndup(char *str, size_t len)
{
	size_t	i;
	char	*copy;

	i = 0;
	copy = NULL;
	if (len == 0)
		return (NULL);
	copy = (char *)malloc(sizeof(char) * len + 1);
	if (copy == NULL)
		return (NULL);
	while (i < len)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

size_t	ft_wordcount(char *s, char c)
{
	size_t	array_size;
	size_t	i;

	i = 0;
	array_size = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c) || \
		(s[i] == c && s[i + 1] != '\0' && s[i + 1] != c))
			array_size++;
		i++;
	}
	return (array_size);
}

char	**ft_split(char *s, char c)
{
	char	**str_array;
	size_t	index;
	size_t	len_str;
	size_t	len_start;

	index = 0;
	len_str = 0;
	str_array = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (str_array && s)
	{
		while (index < ft_wordcount(s, c) && s[len_str] != '\0')
		{
			while (s[len_str] == c)
				len_str++;
			len_start = len_str;
			while (s[len_str] != c && s[len_str] != '\0')
				len_str++;
			str_array[index] = ft_strndup(&s[len_start], len_str - len_start);
			if (str_array[index++] == 0)
				return (ft_freeall(str_array));
		}
		str_array[index] = NULL;
		return (str_array);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	len_s1;
	size_t	len_s2;

	if (s1 && s2)
	{
		i = 0;
		len_s1 = ft_strlen(s1);
		len_s2 = ft_strlen(s2);
		str = (char *)malloc(sizeof(char) * len_s1 + len_s2 + 1);
		if (str == NULL)
			return (NULL);
		while (s1[i] != '\0')
		{
			str[i] = s1[i];
			i++;
		}
		i = 0;
		while (s2[i] != '\0')
			str[len_s1++] = s2[i++];
		str[len_s1] = '\0';
		return (str);
	}
	return (NULL);
}



void	usage_error(char *error_message)
{
	fprintf(stderr, "Error: %s \n", error_message);//
	exit(EXIT_FAILURE);
}

int	path(t_streams *data)
{
	int		i;

	i = 0;
	while (ft_strncmp(data->env[i], "PATH", 4))
		i++;
	if (i == 0)
		return (-1);
	return (0);
}

int	usage_check(int ac, char **av, char *env[], t_streams *data)
{
	if (ac != 5)
		usage_error(ARG_COUNT);
	data->infile = open(av[1], O_RDONLY);
	if (data->infile < 0)
		usage_error(NO_FILE);
	data->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (data->outfile < 0)
		usage_error(NO_FILE);
	data->env = env;
	if (path(data) < 0)
		usage_error(ERROR_PATH);
	return (0);
}

void	clean_close(t_streams *data)
{
	close(data->infile);
	close(data->outfile);
	close(data->fds[1]);
	close(data->fds[0]);
	ft_freeall(data->paths);
	free(data);
}

char *find_path(char *cmd, t_streams *data)
{
	int		i;
	char	**paths;
	char	*url;
	char	*path;

	i = 0;
	while (ft_strnstr(data->env[i], "PATH", 4) ==  0)//
		i++;
	paths = ft_split(data->env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		url = ft_strjoin(paths[i], "/");
		path = ft_strjoin(url, cmd);
		free(url);
		i++;
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths);
	return (0);
}

void	execute(char **av, t_streams *data)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(*av, ' ');
	path = find_path(cmd[0], data);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		usage_error(ERROR_PATH);
	}
	if (execve(path, cmd, data->env) == -1)
		usage_error(ERROR_EXECVE);
}

void parent_pid(char **av, t_streams *data)
{
	dup2(data->fds[0], STDIN_FILENO);
	dup2(data->outfile, STDOUT_FILENO);
	close(data->fds[1]);
	execute(&av[3], data);
}

void child_pid(char **av, t_streams *data)
{
	dup2(data->fds[1], STDIN_FILENO);
	dup2(data->infile, STDOUT_FILENO);
	close(data->fds[0]);
	execute(&av[2], data);
}

int	main(int ac, char **av, char *env[])
{
	t_streams	*data;
	pid_t		pid1;

	data = ft_calloc(1, sizeof(t_streams));
	if (usage_check(ac, av, env, data) == 0)
	{
		if (pipe(data->fds) == -1)
			usage_error(ERROR_PIPE);
		pid1 = fork();
		if (pid1 == -1)
			usage_error(ERROR_PIPE);
		if (pid1 == 0)
			child_pid(av, data);
		waitpid(pid1, NULL, 0);
		parent_pid(av, data);
		clean_close(data);
		return (0);
	}
	else
		clean_close(data);
}
