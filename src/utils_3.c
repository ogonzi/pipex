/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:40:22 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/27 17:40:30 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <stdlib.h>

void	ft_alloc_fd(int ***fd, int num_pipes)
{
	int	i;

	*fd = malloc(sizeof(int *) * num_pipes);
	if (*fd == NULL)
		terminate(ERR_MEM);
	i = -1;
	while (++i < num_pipes)
	{
		(*fd)[i] = malloc(sizeof(int) * 2);
		if ((*fd)[i] == NULL)
			terminate(ERR_MEM);
	}
}

void	ft_free_fd(int ***fd, int num_pipes)
{
	int	i;

	i = -1;
	while (++i < num_pipes)
		free((*fd)[i]);
	free(*fd);
}

void	ft_set_info(t_sys *system, int argc, char **argv, char **env)
{
	system->argv = argv;
	system->env = env;
	system->argc = argc;
	system->heredoc_flag = 0;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc != 6)
		{
			ft_putendl_fd(ERR_ARGS_H, STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		system->heredoc_flag = 1;
	}
	system->num_pipes = argc - 2 - system->heredoc_flag;
	system->num_forks = system->num_pipes - 1;
}

void	ft_dup_and_close(int pipe, int read_write_flag, int ***fd,
			int std_fileno)
{
	if (read_write_flag == 0)
	{
		if (dup2((*fd)[pipe][0], std_fileno) == -1)
			terminate(ERR_DUP);
		if (close((*fd)[pipe][0]) == -1)
			terminate(ERR_CLOSE);
	}
	else
	{
		if (dup2((*fd)[pipe][1], std_fileno) == -1)
			terminate(ERR_DUP);
		if (close((*fd)[pipe][1]) == -1)
			terminate(ERR_CLOSE);
	}
}
