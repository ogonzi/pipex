/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:28:48 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/27 11:48:50 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"
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
