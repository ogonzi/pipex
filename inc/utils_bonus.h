/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:34:19 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/23 13:20:32 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# define ERR_ARGS	"Incorrect number of arguments, expected 5"
# define ERR_OPEN	"Error opening the file"
# define ERR_READ	"Error reading the file"
# define ERR_WRITE	"Error writing to a file"
# define ERR_PIPE	"Error creating pipe"
# define ERR_FORK	"Error forking process"
# define ERR_MEM	"Error allocating memory"
# define ERR_EXEC	"Error executing command"
# define ERR_DUP	"Error duplicating a file descriptor" 
# define ERR_CLOSE	"Error closing a file descriptor"
# define ERR_WAIT	"Error waiting for a process to change state"
# define ERR_QUOTES	"Opening quotes aren't properly closed"

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

/* utils_bonus.c */

void	terminate(char *s);
void	terminate_with_info(int err_code, char *command);
void	ft_free_twod_memory(char **arr);
void	ft_close_fd(int ***fd, int pipe_num);

/* utils_2_bonus.c */

void	ft_remove_char(char *str, char char_to_remove, int first_and_last);

#endif
