/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:59:54 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/21 18:00:19 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "error_message.h"
#include "process_argv.h"
#include "utils.h"
#include "libft.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>

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

/*
 * For a pipe that is not the last the logic is as follows:
 * 1. Duplicate the read end of the pipe on STDIN_FILENO
 * 2. Duplicate the write end of the pipe on STDOUT_FILENO
 * 3. Call execve with the appropiate parameters, which will read from
 * STDIN and output to STDOUT (which have been diverted)
 * If the pipe is the last then an intermediate step is introduced: a file
 * is opened (truncated if it has any content and created if it doesn't exist),
 * and then execve will write to this file with the corresponding dup2 of STDOUT.
 */

void	ft_redirect_pipes(int fd[3][2], t_sys system, t_cmd *cmd, int pid_i)
{
	if (pid_i == 0)
	{
		fd[pid_i][0] = open(system.argv[1], O_RDONLY);
		if (fd[pid_i][0] < 0)
			terminate_with_info(system.err_code, system.argv[1]);
	}
	if (dup2(fd[pid_i][0], STDIN_FILENO) == -1)
		terminate(ERR_DUP);
	if (close(fd[pid_i][0]) == -1)
		terminate(ERR_CLOSE);
	if (pid_i == 1)
	{
		fd[pid_i + 1][1] = open(system.argv[pid_i + 3],
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd[pid_i + 1][1] < 0)
			terminate_with_info(1, system.argv[4]);
	}
	if (dup2(fd[pid_i + 1][1], STDOUT_FILENO) == -1)
		terminate(ERR_DUP);
	if (close(fd[pid_i + 1][1]) == -1)
		terminate(ERR_CLOSE);
	system.err_code = ft_process_argv(system.argv[pid_i + 2], &cmd->split_args,
			&cmd->exec_command, system.env);
	if (execve(cmd->exec_command, cmd->split_args, system.env) == -1)
		terminate_with_info(system.err_code, cmd->split_args[0]);
}

/*
 * The logic for each child is contained in the conditional statement
 * if (pid[i] == 0). All non-used file descriptors are closed and a call
 * to ft_redirect_pipes is executed. Each time a child process ends, exit is
 * called to kill that process.
 */

void	ft_loop_child_processes(int fd[3][2], t_sys system, t_cmd *cmd,
			int *last_pid)
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
			ft_redirect_pipes(fd, system, cmd, i);
			exit(EXIT_SUCCESS);
		}
		else if (i == 1 && pid[i] > 0)
			*last_pid = pid[i];
		i++;
	}
}

/*
 * All fd except fd[0][1] (write end of first pipe) are closed. fd[0][1]
 * is duplicated on STDOUT. Therefore, the call to ft_printf does not print
 * on the terminal, and can be recieved in the reading end of the child
 * process (fd[0][0]). It is necessary to close STDOUT so that commands
 * such as grep don't get stuck infinitelly. Lastly, a loop for the 2 childs
 * is run where each time the wait function is called. If there is an error
 * in the child, the appropiate message and return value are commited.
 */

void	ft_parent_process(int fd[3][2], int last_pid)
{
	int				i;
	t_child_status	child;

	ft_close_fd(fd, 2);
	if (close(fd[2][0]) == -1)
		terminate(ERR_CLOSE);
	if (dup2(fd[0][1], STDOUT_FILENO) < 0)
		terminate(ERR_DUP);
	if (close(fd[0][1]) == -1)
		terminate(ERR_CLOSE);
	i = -1;
	while (++i < 2)
	{
		child.pid = wait(&child.wstatus);
		if (child.pid == -1)
			terminate(ERR_WAIT);
		if (WIFEXITED(child.wstatus))
		{
			child.status_code = WEXITSTATUS(child.wstatus);
			if (child.status_code != 0 && child.pid == last_pid)
				exit(child.status_code);
		}
	}
}

/*
 * 3 pipes are created, therefore 2 calls to fork() are needed to 
 * create 2 child processes and 1 parent process. To follow the behaviour
 * in bash, if any error occurs before cmd2, the processes are allowed to
 * continue and the error message is displayed, but the program returns 0. 
 * If the error occurs in cmd2, the return value is set to the error code.
 * The outfile is always created.
 */

int	main(int argc, char **argv, char **env)
{
	int		fd[3][2];
	int		last_pid;
	t_sys	system;
	t_cmd	cmd;

	if (argc != 5)
	{
		ft_putendl_fd(ERR_ARGS, 2);
		exit(EXIT_FAILURE);
	}
	system.argv = argv;
	system.env = env;
	ft_create_pipes(fd);
	ft_loop_child_processes(fd, system, &cmd, &last_pid);
	ft_parent_process(fd, last_pid);
	return (0);
}
