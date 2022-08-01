/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:23:54 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/01 18:59:05 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "error_message.h"
#include "utils.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

// Remember to treat errors for fork, read, write, etc.
// Add wait to end of parent process (use while loop if there are multiple
// children processes.
// Use O_WRONLY | O_CREATE flags to redirect standard output to outfile.

int	main(int argc, char *argv[])
{
	int	id;
	int	fd[2];

	// fd[0] - read
	// fd[1] - write
	if (argc < 5)
		terminate(ERR_ARGS);
	if (pipe(fd) == -1)
		terminate(ERR_PIPE);
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		int	x;
		printf("Input a number: ");
		scanf("%d", &x);
		write(fd[1], &x, sizeof(int));
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int	y;
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		printf("got from child: %d\n", y);
		wait(NULL);
	}
	(void)argv;
	return (0);
}
