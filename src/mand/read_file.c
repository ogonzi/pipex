/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 09:17:51 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/07 18:34:27 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_message.h"
#include "utils.h"
#include "get_next_line.h"
#include "libft.h"
#include "ft_printf.h"
#include <sys/errno.h>

void	ft_read_line(char **line, int fd)
{
	*line = get_next_line(fd);
	if (!(*line))
	{
		close(fd);
		terminate(ERR_READ);
	}
}

void	ft_get_size(int *size, char *argv[])
{
	int		fd;
	char	*line;

	*size = 0;
	if (access(argv[1], F_OK | R_OK) == -1)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		ft_printf("%s: %s: ", &argv[0][2], argv[1]);
		dup2(STDOUT_FILENO, STDERR_FILENO);
		perror("");
		return ;
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		terminate(ERR_OPEN);
	ft_read_line(&line, fd);
	while (line)
	{
		*size += (int)ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	ft_allocate_memory(char **str, int size)
{
	*str = malloc(sizeof(char) * size);
	if (!(*str))
		terminate(ERR_MEM);
}

void	ft_read_file(char *argv[], char **str)
{
	int		size;
	char	*line;
	int		fd;

	ft_get_size(&size, argv);
	ft_allocate_memory(str, size + 1);
	ft_bzero(*str, sizeof(char) * (size + 1));
	if (size != 0)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			terminate(ERR_READ);
		ft_read_line(&line, fd);
		while (line)
		{
			ft_strlcat(*str, line, size + 1);
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
}
