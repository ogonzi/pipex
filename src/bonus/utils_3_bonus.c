/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:28:48 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/23 14:37:20 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"
#include <stdlib.h>

void	ft_alloc_fd(int ***fd, int argc)
{
	int	i;

	*fd = malloc(sizeof(int *) * (argc - 2));
	if (*fd == NULL)
		terminate(ERR_MEM);
	i = -1;
	while (++i < argc - 2)
	{
		(*fd)[i] = malloc(sizeof(int) * 2);
		if ((*fd)[i] == NULL)
			terminate(ERR_MEM);
	}
}

void	ft_free_fd(int ***fd, int argc)
{
	int	i;

	i = -1;
	while (++i < argc - 2)
		free((*fd)[i]);
	free(*fd);
}
