/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:52:54 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/12 20:21:56 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_child_status
{
	int	wstatus;
	int	status_code;
	int	empty_flag;
	int	pid;
}		t_child_status;

typedef struct s_sys
{
	char	**argv;
	char	**env;
}				t_sys;

typedef struct s_cmd
{
	char	**split_args;
	char	*exec_command;
}			t_cmd;

void	terminate(char *s);
void	ft_free_twod_memory(char **arr);
void	ft_close_fd(int fd[3][2], int pipe_num);
#endif
