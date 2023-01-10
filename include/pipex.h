/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:24:09 by alvachon          #+#    #+#             */
/*   Updated: 2023/01/10 16:06:52 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//cmd1, cmd2 = commands
typedef struct s_streams
{
	int		infile;
	int		outfile;
	int		fds[2];
	char	**paths;
	char	**env;
}	t_streams
;

#endif