/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:48:12 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/13 10:12:12 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error_message.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*
 * If there is no error code given by errno, add error message to stdout 2.
 * If there is an error code, the custom error message is printed, followed by
 * an error message corresponding to the current value of errno.
 */

void	terminate(char *s)
{
	perror(s);
	exit(errno);
}

void	ft_free_twod_memory(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_check_access(char **command, char **paths)
{
	if (access(*command, X_OK) == 0)
	{
		ft_free_twod_memory(paths);
		return (1);
	}
	return (0);
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
