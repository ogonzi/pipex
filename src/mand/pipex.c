/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:23:54 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/04 12:55:33 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "get_next_line.h"
#include "error_message.h"
#include "utils.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

// Remember to treat errors for fork, read, write, etc.
// Add wait to end of parent process (use while loop if there are multiple
// children processeis.
// fd[1] is the write end of the pipe, fd[0] is the read end
// Use O_WRONLY | O_CREATE flags to redirect standard output to outfile.
// Default file descriptors: 0 --> STDIN | 1 --> STDOUT | 2 --> STDERR
// fd2 = dup(fd) [duplicates file descriptor] 
// dup2(fd, STDOUT_FILENO) [Close STDOUT, and then open the file pointed to by fd]
// close fd after using dup2
// To send a string to a parent process, use write(fd[1], sizeof(char) * str, strlen(str) + 1)
// Also, int n = strlen(str) + 1; and write(fd[1], &n, sizeof(int)); 
// In the parent process, read(fd[0], &n, sizeof(int)); and read(fd[0], str, sizeof(char) * n)

void	ft_read_line(char **line, int fd)
{
	*line = get_next_line(fd);
	if (!(*line))
	{
		close(fd);
		terminate(ERR_READ);
	}
}

void	ft_get_size(int *size, char *infile_path)
{
	int		fd;
	char	*line;

	fd = open(infile_path, O_RDONLY);
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
}

void	ft_allocate_memory(char **infile_str, int size)
{
	*infile_str = malloc(sizeof(char) * size);
	if (!(*infile_str))
		terminate(ERR_MEM);
}

void	ft_read_infile(int fd[2], char *infile_path)
{
	int		size;
	char	*infile_str;
	char	*line;

	close(fd[0]);
	ft_get_size(&size, infile_path);
	ft_allocate_memory(&infile_str, size);
	fd[1] = open(infile_path, O_RDONLY);
	ft_read_line(&line, fd[1]);
	while (line)
	{
		ft_strlcat(infile_str, line, size);
		free(line);
		line = get_next_line(fd[1]);
	}
	infile_str[size - 1] = '\0';
	write(fd[1], infile_str, size);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

int	main(int argc, char *argv[])
{
	int	fd[2];
	int	pid[3];

	if (argc != 5)
		terminate(ERR_ARGS);
	if (pipe(fd) == -1)
		terminate(ERR_PIPE);
	pid[0] = fork();
	if (pid[0] < 0)
		terminate(ERR_FORK);
	if (pid[0] == 0)
		ft_read_infile(fd, argv[1]);
	pid[1] = fork();
	if (pid[1] < 0)
		return (2);
	if (pid[1] == 0)
	{
		// Child process 1 (ping)
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]); //read end not used
		close(fd[1]); //since dup2 is used
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	pid[2] = fork();
	if (pid[2] < 0)
		return (3);
	if (pid[2] == 0)
	{
		// Child process 2 (grep)
		dup2(fd[0], STDIN_FILENO); //Waiting to read from pipe
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "round-trip", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	waitpid(pid[2], NULL, 0);
	(void)argv;
	return (0);
}
