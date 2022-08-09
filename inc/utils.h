/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:52:54 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/09 11:58:28 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_child_status
{
	int	wstatus;
	int	status_code;
	int	empty_flag;
}		t_child_status;

void	terminate(char *s);
void	ft_fill_arg_vec(char cmd[10], char *arg_vec[4], char *argv);
void	ft_close_fd(int fd[3][2], int pipe_num);
#endif
