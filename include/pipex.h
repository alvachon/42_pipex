/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:24:09 by alvachon          #+#    #+#             */
/*   Updated: 2023/01/06 19:04:16 by alvachon         ###   ########.fr       */
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
	int		child_pid1;
	int		child_pid2;
	char	**paths;
	char	*cmd1;
	char	*cmd2;
	char	**argvec;
	char	*arg_path;
	char	**envp;
}	t_streams
;

#endif