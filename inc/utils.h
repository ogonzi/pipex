/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:52:54 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/21 18:18:04 by ogonzale         ###   ########.fr       */
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
	int		err_code;
}				t_sys;

typedef struct s_cmd
{
	char	**split_args;
	char	*exec_command;
}			t_cmd;

typedef struct s_error_info
{
	char	*shell;
	char	*shell_line;
	char	*partial_message;
	char	*complete_message;
}			t_error_info;

/* utils.c */

void	terminate(char *s);
void	terminate_with_info(int err_code, char *command);
void	ft_free_twod_memory(char **arr);
void	ft_close_fd(int fd[3][2], int pipe_num);

/* utils_2.c */

void	ft_remove_char(char *str, char char_to_remove, int first_and_last);

#endif
