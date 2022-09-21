/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:01:24 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/21 18:25:24 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "pipex.h"
//#include <stdio.h>

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
			if (!path_line)
				terminate(ERR_MEM);
			*paths = ft_split(path_line, ':');
			if (!(*paths))
				terminate(ERR_MEM);
			free(path_line);
			return ;
		}
		i++;
	}
	**paths = NULL;
}

int	ft_check_access(char **command, char **paths)
{
	if (access(*command, X_OK) == 0)
	{
		if (*paths != NULL)
			ft_free_twod_memory(paths);
		return (1);
	}
	return (0);
}

int	ft_check_script(char **command, char *first_arg, char **paths)
{
	*command = ft_strdup(first_arg);
	if (!(*command))
		terminate(ERR_MEM);
	if (ft_check_access(command, paths) == 1)
	{
		if (ft_strchr((const char *)*command, '/') == NULL)
			exit(127);
		return (1);
	}
	return (0);
}

void	ft_get_full_path(char *path, char **full_path, char *user_command,
			char **command)
{
	*full_path = ft_strjoin(path, "/");
	if (!(*full_path))
		terminate(ERR_MEM);
	*command = ft_strjoin(*full_path, user_command);
	if (!(*command))
		terminate(ERR_MEM);
	free(*full_path);
}

int	ft_process_argv(char *argv, char ***argv_split, char **command,
			char *env[])
{
	char	**paths;
	char	*full_path;
	int		i;

	ft_get_paths(&paths, env);
	*argv_split = ft_split_mod(argv, " \t\n");
	i = 0;
	while (paths[i] != NULL)
	{
		ft_get_full_path(paths[i], &full_path, *argv_split[0], command);
		if (ft_check_access(command, paths) == 1)
			return (0);
		free(*command);
		i++;
	}
	if (ft_check_script(command, *argv_split[0], paths) == 1)
		return (0);
	if (*paths != NULL)
		ft_free_twod_memory(paths);
	if (ft_strchr((const char *)*command, '/') == NULL)
		return (127);
	return (126);
}
