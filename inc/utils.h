/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:38:07 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/27 17:43:38 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define ERR_ARGS	"Incorrect number of arguments, expected 5 or more"
# define ERR_ARGS_H	"Incorrect number of arguments, expected 6"
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
	int		argc;
	int		num_pipes;
	int		num_forks;
	int		heredoc_flag;
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
void	ft_close_fd(int ***fd, int pipe_num, int num_pipes);

/* utils_2.c */

void	ft_open_infile(int pid_i, int ***fd, t_sys system);
void	ft_open_outfile(int pid_i, int ***fd, t_sys system);
void	ft_input_to_output(int pid_i, int ***fd, t_sys system);

/* utils_3.c */

void	ft_alloc_fd(int ***fd, int num_pipes);
void	ft_free_fd(int ***fd, int num_pipes);
void	ft_set_info(t_sys *system, int argc, char **argv, char **env);
void	ft_dup_and_close(int pid_i, int read_write_flag, int ***fd,
			int std_fileno);

#endif
