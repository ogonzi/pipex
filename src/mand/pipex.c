/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:23:54 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/01 13:28:56 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "error_message.h"
#include "utils.h"
#include "libft.h"
#include <unistd.h>

const char *process = NULL;

void	read_from_fd(int fd)
{
	char	c;
	ft_printf("Process [%s] Reading from descriptor %d \n", process, fd);
	while (read(fd, &c, 1) != 0)
		ft_printf("%c", c);
}

int	main(int argc, char *argv[])
{
	int	fd[2];
	int	pid;
	const char *data;

	process = "PARENT";
	if (argc < 5)
		terminate(ERR_ARGS);
	if (pipe(fd) != 0)
		terminate(ERR_PIPE);
	pid = fork();
	if (pid == -1)
		terminate(ERR_PIPE);
	else if (pid == 0)
	{
		process = "CHILD";
		close(fd[1]);
		read_from_fd(fd[0]);
		exit(0);
	}
	else
	{
		close(fd[0]);
		data = "Data";
		ft_printf("Process [%s] Writing data to pipe \n", process);
		ft_printf("pid = %d\n", pid);
		write(fd[1], data, ft_strlen(data));
		close(fd[1]);
		waitpid(pid, 0, 0);
		exit(0);
	}
	(void)argv;
	return (0);
}
