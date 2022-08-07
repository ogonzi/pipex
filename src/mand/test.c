/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 13:10:52 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/06 13:17:18 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int	main(int argc, char *argv[])
{
	int	fd[3][2];
	int	pid[2];
	int	i;
	int	j;

	if (argc != 4)
		return (1);
	i = 0;
	while (i < 3)
	{
		if (pipe(fd[i]) < 0)
			return (2);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (3);
		if (pid[i] == 0)
		{
			j = 0;
			while (j < 3)
			{
				if (i != j)
					close(fd[j][0]);
				if (i + 1 != j)
					close(fd[j][1]);
				j++;
			}
		}
		i++;
	}
}
