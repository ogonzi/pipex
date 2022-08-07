/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:23:54 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/07 09:37:00 by ogonzale         ###   ########.fr       */
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

void	ft_fill_arg_vec(char cmd[10], char *arg_vec[4], char *argv)
{
	arg_vec[0] = cmd;
	arg_vec[1] = "-c";
	arg_vec[2] = argv;
	arg_vec[3] = NULL;
}
/*
void	ft_redirect_pipes(int fd[3][2], char *command, int pipe_num)
{
	char	cmd[10];
	char	*arg_vec[4];

	printf("[(pipe %d) ft_redirect_pipes]\n", pipe_num);
	ft_strlcpy(cmd, "/bin/bash", 10);
	printf("(pipe %d) closing fd[%d][0]\n", pipe_num, pipe_num);
	dup2(fd[pipe_num][0], STDIN_FILENO);
	close(fd[pipe_num][0]);
	if (outfile_path)
	{
		printf("Opening/creating outfile\n");
		fd[pipe_num + 1][1] = open(outfile_path, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (fd[pipe_num + 1][1] < 0)
			terminate(ERR_OPEN);
	}
	printf("(pipe %d) closing fd[%d][1]\n", pipe_num, pipe_num + 1);
	printf("%s\n", command);
	dup2(fd[pipe_num + 1][1], STDOUT_FILENO);
	close(fd[pipe_num + 1][1]);
	ft_fill_arg_vec(cmd, arg_vec, command);
	if (execve(cmd, arg_vec, NULL) == -1)
		terminate(ERR_EXEC);
}
*/
int	main(int argc, char *argv[])
{
	char	*infile_str;

	if (argc != 5)
		terminate(ERR_ARGS);
	ft_read_file(argv[1], &infile_str);
	printf("%s", infile_str);
	return (0);
}
