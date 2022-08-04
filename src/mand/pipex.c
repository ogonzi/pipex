/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:23:54 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/04 18:06:13 by ogonzale         ###   ########.fr       */
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
// dup2(fd, STDOUT_FILENO) [Close STDOUT, and then open the file pointed to
// by fd]
// close fd after using dup2
// To send a string to a parent process, use write(fd[1], sizeof(char) * str,
// strlen(str) + 1)
// Also, int n = strlen(str) + 1; and write(fd[1], &n, sizeof(int)); 
// In the parent process, read(fd[0], &n, sizeof(int)); and read(fd[0], str,
// sizeof(char) * n)

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

void	ft_read_infile(int fd[3][2], char *infile_path)
{
	int		size;
	char	*infile_str;
	char	*line;

	close(fd[2][0]);
	ft_get_size(&size, infile_path);
	ft_allocate_memory(&infile_str, size);
	fd[0][1] = open(infile_path, O_RDONLY);
	ft_read_line(&line, fd[0][1]);
	while (line)
	{
		ft_strlcat(infile_str, line, size);
		free(line);
		line = get_next_line(fd[0][1]);
	}
	infile_str[size - 1] = '\0';
	write(fd[0][1], infile_str, size);
	dup2(fd[0][1], STDOUT_FILENO);
	close(fd[0][1]);
}

void	ft_fill_arg_vec(char cmd[10], char *arg_vec[4], char *argv)
{
	arg_vec[0] = cmd;
	arg_vec[1] = "-c";
	arg_vec[2] = argv;
	arg_vec[3] = NULL;
}

void	ft_close_fd(int fd[3][2], int pipe_num)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 2)
		{
			if ((i == pipe_num && j == 0) || (i == pipe_num + 1 && j == 1))
				;
			else
				close(fd[i][j]);
			j++;
		}
		i++;
	}
}

void	ft_redirect_pipes(int fd[3][2], char *command, int pipe_num,
			char *outfile_path)
{
	char	cmd[10];
	char	*arg_vec[4];

	ft_strlcpy(cmd, "/bin/bash", 10);
	dup2(fd[pipe_num][0], STDIN_FILENO);
	close(fd[pipe_num][0]);
	if (outfile_path)
	{
		fd[pipe_num + 1][1] = open(outfile_path, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (fd[pipe_num + 1][1] < 0)
			terminate(ERR_OPEN);
	}
	dup2(fd[pipe_num + 1][1], STDOUT_FILENO);
	close(fd[pipe_num + 1][1]);
	ft_fill_arg_vec(cmd, arg_vec, command);
	if (execve(cmd, arg_vec, NULL) == -1)
		terminate(ERR_EXEC);
}

int	main(int argc, char *argv[])
{
	int		fd[3][2];
	int		pid[2];
	int		i;

	if (argc != 5)
		terminate(ERR_ARGS);
	i = 0;
	while (i < 3)
	{
		if (pipe(fd[i]) < 0)
			terminate(ERR_PIPE);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			terminate(ERR_FORK);
		if (pid[i] == 0)
		{
			ft_close_fd(fd, i);
			if (i != 1)
				ft_redirect_pipes(fd, argv[i + 2], i, 0);
			else
				ft_redirect_pipes(fd, argv[i + 2], i, argv[i + 3]);
			return (0);
		}
		i++;
	}
	ft_close_fd(fd, 2);
	ft_read_infile(fd, argv[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}
