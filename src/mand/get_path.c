/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:01:24 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/10 18:01:45 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <stdio.h>

void	ft_get_paths(char ***paths, char *env[])
{
	int		i;
	char	*path_line;
	
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strnstr(env[i], "PATH", ft_strlen(env[i])) != NULL)
		{
			path_line = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			*paths = ft_split(path_line, ':');
			free(path_line);
			break ;
		}
		i++;
	}
}

void	ft_split_argv(char **command, char **options, char *argv_cmd)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(argv_cmd))
	{
		if (argv_cmd[i] == ' ')
		{
			*command = ft_substr(argv_cmd, 0, i);
			*options = ft_substr(argv_cmd, i + 1, ft_strlen(argv_cmd) - i);
			break ;
		}
		i++;
	}

}

void	ft_get_command(char **cmd, char **options, char *argv_cmd, char *env[])
{
	char	**paths;
	char	*path_with_bar;
	char	*command;
	int		i;

	ft_get_paths(&paths, env);
	ft_split_argv(&command, options, argv_cmd);
	i = 0;
	while (paths[i] != NULL)
	{
		path_with_bar = ft_strjoin(paths[i], "/");
		if (*options != NULL)
			*cmd = ft_strjoin(path_with_bar, command);
		else
			*cmd = ft_strjoin(path_with_bar, argv_cmd);
		free(path_with_bar);
		if (access(*cmd, X_OK) == 0)
			break ;
		free(*cmd);
		*cmd = NULL;
		i++;
	}
}

void	ft_fill_args_cmd(char *cmd, char *options, char ***args_cmd)
{
	int	num_options;

	num_options = ft_get_num_options(options);
	fprintf(stderr, "num_options = %d\n", num_options);
	fprintf(stderr, "cmd = %s\n", cmd);
	(void)args_cmd;
}
