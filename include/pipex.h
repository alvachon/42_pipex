/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:24:09 by alvachon          #+#    #+#             */
/*   Updated: 2023/01/18 21:11:49 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define ARG_COUNT "Problem with the number of argument.\n"
# define NO_FILE "Problem with presence of file.\n"
# define ERROR_COMMAND "Problem with validity of command.\n"
# define ERROR_PIPE "Problem with the pipe stream (fds[0], fds[1]).\n"
# define ERROR_PATH "Problem with the environ path. \n"
# define ERROR_EXECVE "Problem with execve. \n"

/* CHILD CREATED, PIPE IN:
1. close unused gate(fds[0])
2. link infile fd as stdin with dup2
3. link exit pipe (fds[1]) as stdout with dup2
now good info on standard fd 0 and 1 (stdin, stdout) for first part. */
void	child_pipe_in(char **av, int *fds, char *env[]);

/* PIPE OUT :
1. close unused gate(fds[1])
2. link entry pipe (fds[0]) as stdin with dup2
3. link outfile fd (result) as stdout with dup2
now good info on standard fd 0 and 1 (stdin, stdout) for second part.*/
void	pipe_out(char **av, int *fds, char *env[]);

/* Find the access if one, execute command if one. */
void	execute_token(char *av, char *env[]);
char	*find_path(char *cmd, char *env[]);

char	**ft_freeall(char **str);
void	error(char *error_message);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

size_t	ft_strlen(const char *s);
char	*ft_strndup(char *str, size_t len);
size_t	ft_wordcount(char *s, char c);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);

#endif