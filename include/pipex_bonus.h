/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:49:46 by alvachon          #+#    #+#             */
/*   Updated: 2023/01/18 21:24:53 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../include/pipex.h"

# define HERE_DOC "argument(1) not here_doc \n"
# define WRITE_CREATE_APPEND 1
# define WRITE_CREATE_TRUNC 2
# define READ 3
# define RWX 0777

void	redirect_heredoc(char *token);
int		heredoc(char **line);

int		open_selector(char *file, int flag);
void	pipex(char *av, char *env[]);
int		bonus(int ac, char **av, char *env[]);

void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif