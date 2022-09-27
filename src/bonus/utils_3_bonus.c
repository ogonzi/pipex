/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:28:48 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/27 10:31:20 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"
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
