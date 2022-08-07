/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:48:12 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/07 13:53:15 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error_message.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

/*
 * If there is no error code given by errno, add error message to stdout 2.
 * If there is an error code, the custom error message is printed, followed by
 * an error message corresponding to the current value of errno.
 */

void	terminate(char *s)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(errno);
}

void	ft_fill_arg_vec(char cmd[10], char *arg_vec[4], char *argv)
{
	arg_vec[0] = cmd;
	arg_vec[1] = "-c";
	arg_vec[2] = argv;
	arg_vec[3] = NULL;
}

void	ft_close_fd(int fd[3][2], int pipe_num)
{
	int	j;

	j = 0;
	while (j < 3)
	{
		if (pipe_num != j)
			close(fd[j][0]);
		if ((pipe_num + 1) % 3 != j)
			close(fd[j][1]);
		j++;
	}
}
