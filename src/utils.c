/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:39:51 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/27 17:39:59 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
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

void	ft_compose_message(t_error_info *error_info, char *command,
							int err_code)
{
	char	*command_err;

	error_info->partial_message = ft_strjoin(error_info->shell, ": ");
	if (!error_info->partial_message)
		terminate(ERR_MEM);
	free(error_info->shell);
	error_info->complete_message = ft_strjoin(error_info->partial_message,
			command);
	if (!error_info->complete_message)
		terminate(ERR_MEM);
	free(error_info->partial_message);
	if (err_code != 127)
		perror(error_info->complete_message);
	else
	{
		command_err = ft_strjoin(error_info->complete_message,
				": command not found");
		if (command_err == NULL)
			terminate(ERR_MEM);
		ft_putendl_fd(command_err, STDERR_FILENO);
	}
}

void	terminate_with_info(int err_code, char *command)
{
	t_error_info	error_info;

	error_info.shell = malloc(sizeof(char) * (ft_strlen("bash") + 1));
	if (error_info.shell == NULL)
		terminate(ERR_MEM);
	ft_strlcpy(error_info.shell, "bash", 5);
	ft_compose_message(&error_info, command, err_code);
	exit(err_code);
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

/*
 * Closes all file descriptors except the read and write end of 
 * the current child. Ex. if pid = 1, then all fd are closed
 * except fd[1][0] and fd[2][1].
 */

void	ft_close_fd(int ***fd, int pipe_num, int num_pipes)
{
	int	j;

	j = 0;
	while (j < num_pipes)
	{
		if (pipe_num != j)
			if (close((*fd)[j][0]) == -1)
				terminate(ERR_CLOSE);
		if ((pipe_num + 1) % num_pipes != j)
			if (close((*fd)[j][1]) == -1)
				terminate(ERR_CLOSE);
		j++;
	}
}
