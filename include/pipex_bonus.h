/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:49:46 by alvachon          #+#    #+#             */
/*   Updated: 2023/01/18 18:49:12 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../include/pipex.h"

char	*ft_strjoin(char const *s1, char const *s2);

void	error(char *error_message);
void	ft_putstr_fd(char *s, int fd);

#endif