/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:31:27 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/27 15:34:28 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "utils_bonus.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

void	ft_create_pipes(int ***fd, int num_pipes)
{
	int	i;

	i = -1;
	while (++i < num_pipes)
		if (pipe((*fd)[i]) < 0)
			terminate(ERR_PIPE);
}

void	ft_redirect_pipes(int ***fd, t_sys system, t_cmd *cmd, int pid_i)
{
	char	*line;

	if (pid_i == 0)
	{
		if (system.heredoc_flag == 0)
		{
			(*fd)[pid_i][0] = open(system.argv[1], O_RDONLY);
			if ((*fd)[pid_i][0] < 0)
				terminate_with_info(system.err_code, system.argv[1]);
		}
		else
		{
			/*
			line = get_next_line(STDIN_FILENO);
			ft_printf("%s", line);
			while (ft_strncmp(line, system.argv[2], ft_strlen(system.argv[2])) != 0)
			{
				line = get_next_line(STDIN_FILENO);
				ft_printf("%s", line);
			}
			*/
		}
	}
	if (pid_i != 0 || system.heredoc_flag == 0)
	{
		if (dup2((*fd)[pid_i][0], STDIN_FILENO) == -1)
			terminate(ERR_DUP);
		if (close((*fd)[pid_i][0]) == -1)
			terminate(ERR_CLOSE);
	}
	if (pid_i == system.num_forks - 1)
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
	if (dup2((*fd)[pid_i + 1][1], STDOUT_FILENO) == -1)
		terminate(ERR_DUP);
	if (pid_i == 0 && system.heredoc_flag == 1)
	{
		line = get_next_line(STDIN_FILENO);
		if (system.argv[2] == NULL)
			ft_printf("%s", line);
		while (system.argv[2] != NULL
				&&( ft_strncmp(line, system.argv[2], ft_strlen(line) - 1) != 0
				|| ft_strncmp(line, system.argv[2], ft_strlen(system.argv[2])) != 0))
		{
			ft_printf("%s", line);
			free(line);
			line = get_next_line(STDIN_FILENO);
		}
		free(line);
		if (dup2((*fd)[pid_i][0], STDIN_FILENO) == -1)
			terminate(ERR_DUP);
		if (close((*fd)[pid_i][0]) == -1)
			terminate(ERR_CLOSE);
	}
	if (close((*fd)[pid_i + 1][1]) == -1)
		terminate(ERR_CLOSE);
	system.err_code = ft_process_argv(system.argv[pid_i + system.heredoc_flag + 2],
			&cmd->split_args, &cmd->exec_command, system.env);
	if (execve(cmd->exec_command, cmd->split_args, system.env) == -1)
		terminate_with_info(system.err_code, cmd->split_args[0]);
}

void	ft_loop_child_processes(int ***fd, t_sys system, t_cmd *cmd,
			int *last_pid)
{
	int	*pid;
	int	i;

	pid = malloc(sizeof(int) * system.num_forks);
	if (pid == NULL)
		terminate(ERR_MEM);
	i = -1;
	while (++i < system.num_forks)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			terminate(ERR_FORK);
		if (pid[i] == 0)
		{
			ft_close_fd(fd, i, system.num_pipes);
			ft_redirect_pipes(fd, system, cmd, i);
			exit(EXIT_SUCCESS);
		}
		else if (i == system.num_forks - 1 && pid[i] > 0)
			*last_pid = pid[i];
	}
	free(pid);
}

void	ft_parent_process(int ***fd, int last_pid, t_sys system)
{
	int				i;
	t_child_status	child;

	ft_close_fd(fd, system.num_forks, system.num_pipes);
	if (close((*fd)[system.num_forks][0]) == -1)
		terminate(ERR_CLOSE);
	if (close((*fd)[0][1]) == -1)
		terminate(ERR_CLOSE);
	i = -1;
	while (++i < system.num_forks)
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

int	main(int argc, char **argv, char **env)
{
	int		**fd;
	int		last_pid;
	t_sys	system;
	t_cmd	cmd;

	if (argc < 5)
	{
		ft_putendl_fd(ERR_ARGS, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ft_set_info(&system, argc, argv, env);
	ft_alloc_fd(&fd, system.num_pipes);
	ft_create_pipes(&fd, system.num_pipes);
	ft_loop_child_processes(&fd, system, &cmd, &last_pid);
	ft_parent_process(&fd, last_pid, system);
	ft_free_fd(&fd, system.num_pipes);
	return (0);
}
