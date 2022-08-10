/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:48:12 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/10 18:15:26 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error_message.h"
#include <stdio.h>

/*
 * If there is no error code given by errno, add error message to stdout 2.
 * If there is an error code, the custom error message is printed, followed by
 * an error message corresponding to the current value of errno.
 */

void	terminate(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

int	ft_get_num_options(char *options)
{
	int	i;
	int	num_options;

	num_options = 0;
	i = 0;
	while (options[i] != '\0')
	{
		if (!ft_isspace(options[i]) && (ft_isspace(options[i - 1]) || i == 0))
		{
			if (options[i] == '\"')
			{
				i++;
				while (options[i] != '\"')
				{
					if (options[i] == '\0')
						terminate(ERR_QUOTES);
					i++;
				}
			}
			num_options++;
		}
		i++;
	}
	return (num_options);
}

void	ft_fill_arg_vec(char *cmd, char *arg_vec[3], char *options)
{
	arg_vec[0] = cmd;
	arg_vec[1] = options;
	arg_vec[2] = NULL;
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
