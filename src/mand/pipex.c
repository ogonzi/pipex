/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:23:54 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/07 11:07:08 by ogonzale         ###   ########.fr       */
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
int	main(int argc, char *argv[], char **env)
{
	char	*infile_str;
	int		pid1;
	int		pid2;
	int		fd[3][2];
	int		i;

	if (argc != 5)
		terminate(ERR_ARGS);
	ft_read_file(argv[1], &infile_str);
	i = 0;
	while (i < 3)
	{
		if (pipe(fd[i]) < 0)
			terminate(ERR_PIPE);
		i++;
	}
	pid1 = fork();
	if (pid1 < 0)
		terminate(ERR_FORK);
	if (pid1 == 0)
	{
		char	cmd[10];
		char	*arg_vec[4];

		ft_strlcpy(cmd, "/bin/bash", 10);
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][0]);
		close(fd[2][1]);
		if (dup2(fd[0][0], STDIN_FILENO) < 0)
			terminate(ERR_DUP);
		close(fd[0][0]);
		if (dup2(fd[1][1], STDOUT_FILENO) < 0)
			terminate(ERR_DUP);
		close(fd[1][1]);
		ft_fill_arg_vec(cmd, arg_vec, argv[2]);
		if (execve(cmd, arg_vec, env) < 0)
			terminate(ERR_EXEC);
		return (0);
	}
	pid2 = fork();
	if (pid2 < 0)
		terminate(ERR_FORK);
	if (pid2 == 0)
	{
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[2][0]);
		close(fd[2][1]);
		
		char	*res_str;

		res_str = malloc(100);
		if (read(fd[1][0], res_str, 100) < 0)
			terminate(ERR_READ);
		ft_printf("%s", res_str);
		free(res_str);
		close(fd[1][0]);
		/*
		ft_read_file(fd[1][0], &res_str);
		close(fd[1][0]);
		fd[2][1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (fd[2][1] < 0)
			terminate(ERR_OPEN);
		if (dup2(fd[2][1], STDOUT_FILENO) < 0)
			terminate(ERR_DUP);
		close(fd[2][1]);
		ft_printf("%s", res_str);
		*/
		return (0);
	}
	close(fd[0][0]);
	close(fd[1][0]);
	close(fd[1][1]);
	close(fd[2][0]);
	close(fd[2][1]);
	/*
	size = sizeof(char) * ft_strlen(infile_str);
	if (write(fd[0][1], &size, sizeof(int)) < 0)
		terminate(ERR_WRITE);
	if (write(fd[0][1], infile_str, size) < 0)
		terminate(ERR_WRITE);
	*/
	if (dup2(fd[0][1], STDOUT_FILENO) < 0)
		terminate(ERR_DUP);
	close(fd[0][1]);
	ft_printf("%s", infile_str);
	free(infile_str);
	//close(0);
	close(1);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
