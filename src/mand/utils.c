/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:48:12 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/13 13:18:59 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error_message.h"
#include "utils.h"
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

void	ft_compose_message(t_error_info *error_info, char *command)
{
	error_info->partial_message = ft_strjoin(error_info->shell, ": ");
	if (!error_info->partial_message)
		terminate(ERR_MEM);
	free(error_info->shell);
	error_info->complete_message = ft_strjoin(error_info->partial_message,
			command);
	if (!error_info->complete_message)
		terminate(ERR_MEM);
	free(error_info->partial_message);
	free(command);
}

void	terminate_with_info(char **env, char *command)
{
	t_error_info	error_info;
	int				i;

	i = 0;
	error_info.shell = NULL;
	while (env[i] != NULL)
	{
		if (ft_strnstr(env[i], "SHELL", ft_strlen(env[i])) != NULL)
		{
			error_info.shell_line = ft_substr(env[i], 6, ft_strlen(env[i]) - 6);
			if (!error_info.shell_line)
				terminate(ERR_MEM);
			error_info.shell = ft_strdup(ft_strrchr(error_info.shell_line, '/')
					+ sizeof(char));
			if (!error_info.shell)
				terminate(ERR_MEM);
			free(error_info.shell_line);
			break ;
		}
		i++;
	}
	ft_compose_message(&error_info, command);
	perror(error_info.complete_message);
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
		{
			if (close(fd[j][0]) == -1)
				terminate(ERR_CLOSE);
		}
		if ((pipe_num + 1) % 3 != j)
		{
			if (close(fd[j][1]) == -1)
				terminate(ERR_CLOSE);
		}
		j++;
	}
}
