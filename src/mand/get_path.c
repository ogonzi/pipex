/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:01:24 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/09 18:13:42 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_get_command(char **cmd, char **options, char *argv_cmd, char *env[])
{
	char	**paths;
	char	*path_line;
	char	*path_with_bar;
	char	*command;
	int		i;
	int		j;

	i = 0;
	paths = NULL;
	while (env[i] != NULL)
	{
		if (ft_strnstr(env[i], "PATH", ft_strlen(env[i])) != NULL)
		{
			path_line = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			paths = ft_split(path_line, ':');
			free(path_line);
			break ;
		}
		i++;
	}
	i = 0;
	command = NULL;
	*options = NULL;
	j = 0;
	while (j < (int)ft_strlen(argv_cmd))
	{
		if (argv_cmd[j] == ' ')
		{
			command = ft_substr(argv_cmd, 0, j);
			*options = ft_substr(argv_cmd, j + 1, ft_strlen(argv_cmd) - j);
			break ;
		}
		j++;
	}
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
