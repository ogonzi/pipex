/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:40:08 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/27 17:40:17 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "libft.h"
#include <fcntl.h>

void	ft_open_infile(int pid_i, int ***fd, t_sys system)
{
	(*fd)[pid_i][0] = open(system.argv[1], O_RDONLY);
	if ((*fd)[pid_i][0] < 0)
		terminate_with_info(system.err_code, system.argv[1]);
}

void	ft_open_outfile(int pid_i, int ***fd, t_sys system)
{
	if (system.heredoc_flag == 0)
	{
		(*fd)[pid_i + 1][1] = open(system.argv[system.argc - 1],
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	else
	{
		(*fd)[pid_i + 1][1] = open(system.argv[system.argc - 1],
				O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
	if ((*fd)[pid_i + 1][1] < 0)
		terminate_with_info(1, system.argv[system.argc - 1]);
}

void	ft_input_to_output(int pid_i, int ***fd, t_sys system)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	if (line == NULL)
		terminate(ERR_MEM);
	if (system.argv[2] == NULL)
		ft_printf("%s", line);
	while (system.argv[2] != NULL
		&& (ft_strncmp(line, system.argv[2], ft_strlen(line) - 1) != 0
			|| ft_strncmp(line, system.argv[2], ft_strlen(system.argv[2]))
			!= 0))
	{
		ft_printf("%s", line);
		free(line);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			terminate(ERR_MEM);
	}
	free(line);
	ft_dup_and_close(pid_i, 0, fd, STDIN_FILENO);
}
