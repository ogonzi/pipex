/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:23:54 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/08 09:54:31 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "get_next_line.h"
#include "error_message.h"
#include "utils.h"
#include "read_file.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/errno.h>

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

void	ft_create_pipes(int fd[3][2])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (pipe(fd[i]) < 0)
			terminate(ERR_PIPE);
		i++;
	}
}

void	ft_redirect_pipes(int fd[3][2], char *argv[], int pipe_num, char **env)
{
	char	cmd[10];
	char	*arg_vec[4];

	ft_strlcpy(cmd, "/bin/bash", 10);
	dup2(fd[pipe_num][0], STDIN_FILENO);
	close(fd[pipe_num][0]);
	if (pipe_num == 1)
	{
		fd[pipe_num + 1][1] = open(argv[pipe_num + 3],
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd[pipe_num + 1][1] < 0)
			terminate(ERR_OPEN);
	}
	dup2(fd[pipe_num + 1][1], STDOUT_FILENO);
	close(fd[pipe_num + 1][1]);
	ft_fill_arg_vec(cmd, arg_vec, argv[pipe_num + 2]);
	if (execve(cmd, arg_vec, env) == -1)
		terminate(ERR_EXEC);
}

void	ft_loop_child_processes(int fd[3][2], char *argv[], char **env)
{
	int	pid[2];
	int	i;

	i = 0;
	while (i < 2)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			terminate(ERR_FORK);
		if (pid[i] == 0)
		{
			ft_close_fd(fd, i);
			ft_redirect_pipes(fd, argv, i, env);
			exit(0);
		}
		i++;
	}
}

void	ft_parent_process(int fd[3][2], char *infile_str)
{
	int	i;
	int	wstatus;
	int	status_code;

	ft_close_fd(fd, 2);
	close(fd[2][0]);
	if (dup2(fd[0][1], STDOUT_FILENO) < 0)
		terminate(ERR_DUP);
	close(fd[0][1]);
	ft_printf("%s", infile_str);
	free(infile_str);
	close(STDOUT_FILENO);
	i = -1;
	while (++i < 2)
	{
		wait(&wstatus);
		if (WIFEXITED(wstatus) && ft_strlen(infile_str))
		{
			status_code = WEXITSTATUS(wstatus);
			if (status_code != 0 && i == 1)
				exit(status_code);
		}
	}
}

int	main(int argc, char *argv[], char **env)
{
	char	*infile_str;
	int		fd[3][2];

	if (argc != 5)
		terminate(ERR_ARGS);
	ft_read_file(argv, &infile_str);
	ft_create_pipes(fd);
	ft_loop_child_processes(fd, argv, env);
	ft_parent_process(fd, infile_str);
	return (0);
}
