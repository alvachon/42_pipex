/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:46:36 by alvachon          #+#    #+#             */
/*   Updated: 2023/01/18 21:23:07 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (fd);
}

void	redirect_heredoc(char *token)
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