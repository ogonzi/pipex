/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 09:17:51 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/07 13:07:00 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_message.h"
#include "utils.h"
#include "get_next_line.h"
#include "libft.h"

void	ft_read_line(char **line, int fd)
{
	*line = get_next_line(fd);
	if (!(*line))
	{
		close(fd);
		terminate(ERR_READ);
	}
}

void	ft_get_size(int *size, char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		terminate(ERR_OPEN);
	*size = 0;
	ft_read_line(&line, fd);
	while (line)
	{
		*size += (int)ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	(*size)++;
}

void	ft_allocate_memory(char **str, int size)
{
	*str = malloc(sizeof(char) * size);
	if (!(*str))
		terminate(ERR_MEM);
}

void	ft_read_file(char *path, char **str)
{
	int		size;
	char	*line;
	int		fd;

	ft_get_size(&size, path);
	ft_allocate_memory(str, size);
	ft_bzero(*str, size);
	fd = open(path, O_RDONLY);
	ft_read_line(&line, fd);
	while (line)
	{
		ft_strlcat(*str, line, size);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	str[size] = "\0";
}
