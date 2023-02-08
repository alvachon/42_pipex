/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:24:09 by alvachon          #+#    #+#             */
/*   Updated: 2023/01/24 19:36:24 by alvachon         ###   ########.fr       */
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
# define ERROR_COMMAND "Problem with validity of the command.\n"
# define ERROR_PIPE "Problem with the pipe stream or the standard fd (0, 1).\n"
# define ERROR_PATH "Problem with the environ path. \n"
# define ERROR_EXECVE "Problem with execve. \n"
# define RWX 0777

/*pipex.c */
int		main(int ac, char **av, char *env[]);
void	child_pipe_in(char **av, int *fds, char *env[]);
void	pipe_out(char **av, int *fds, char *env[]);

/*execute.c */
void	execute_token(char *av, char *env[]);
char	**ft_split(char *s, char c);
size_t	ft_wordcount(char *s, char c);
char	*ft_strndup(char *str, size_t len);

/*path.c */
char	*find_path(char *cmd, char *env[]);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/*return .c*/
void	error(char *error_message);
void	ft_putstr_fd(char *s, int fd);
char	**ft_freeall(char **str);

#endif