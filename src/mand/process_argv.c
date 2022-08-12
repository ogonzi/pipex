/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:01:24 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/12 20:23:52 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "split.h"
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

void	ft_process_argv(char *argv, char ***argv_split, char **command,
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
		full_path = ft_strjoin(paths[i], "/");
		*command = ft_strjoin(full_path, *argv_split[0]);
		free(full_path);
		if (access(*command, X_OK) == 0)
		{
			ft_free_twod_memory(paths);
			return ;
		}
		free(*command);
		i++;
	}
	*command = ft_strdup(*argv_split[0]);
	if (access(*command, X_OK) == 0)
	{
		ft_free_twod_memory(paths);
		return ;
	}
	free(*command);
	*command = NULL;
}
