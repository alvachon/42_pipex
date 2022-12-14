/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 20:21:54 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/13 21:07:40 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int	main(int ac, char **av)
{
	int	fd[2];
	int	child_pid1;
	int	child_pid2;

	if (pipe(fd) == -1)
		return (1);
	child_pid1 = fork();
	if (child_pid1 < 0)
	{
		perror("fork");
		return (2);
	}
	if (child_pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	child_pid2 = fork();
	if (child_pid2 < 0)
	{
		perror("fork");
		return (3);
	}
	if (child_pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "rtt", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(child_pid2, NULL, 0);
	waitpid(child_pid1, NULL, 0);
	return (0);
}
