/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:39:34 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/27 17:39:44 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "pipex.h"

void	ft_skip_quoted(const char *str, int *i, char c)
{
	if (str[*i] == c)
	{
		(*i)++;
		while (str[*i] != c)
		{
			if (str[*i] == '\0')
				terminate(ERR_QUOTES);
			if (str[*i] == '\\' && str[*i + 1] == c)
				(*i)++;
			(*i)++;
		}
	}
}

void	ft_split_logic(const char *str, const char *sep, int *i, int *old_i)
{
	while (str[*i] != '\0')
	{
		if (ft_strchr(sep, str[*i]) == NULL)
			break ;
		(*i)++;
	}
	*old_i = *i;
	while (str[*i] != '\0')
	{
		ft_skip_quoted(str, i, '\'');
		ft_skip_quoted(str, i, '\"');
		if (ft_strchr(sep, str[*i]) != NULL)
			break ;
		(*i)++;
	}
}

void	ft_get_count(const char *str, const char *sep, int *count)
{
	int	i;
	int	old_i;

	i = 0;
	*count = 0;
	while (str[i] != '\0')
	{
		ft_split_logic(str, sep, &i, &old_i);
		if (i > old_i)
			(*count)++;
	}
}

void	ft_get_splits(char **str_split, const char *str, const char *sep)
{
	int	i;
	int	old_i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		ft_split_logic(str, sep, &i, &old_i);
		if (i > old_i)
		{
			if (str[old_i] == '\'' || str[old_i] == '\"')
				str_split[j] = ft_substr(str, old_i + 1, i - old_i - 2);
			else
				str_split[j] = ft_substr(str, old_i, i - old_i);
			ft_remove_char(str_split[j], '\\', 0);
			if (!str_split[j])
			{
				ft_free_twod_memory(str_split);
				terminate(ERR_MEM);
			}
			j++;
		}
	}
	str_split[j] = NULL;
}

char	**ft_split_mod(const char *str, const char *sep)
{
	int		num_splits;
	char	**str_split;

	ft_get_count(str, sep, &num_splits);
	str_split = malloc(sizeof(char *) * (num_splits + 1));
	if (!str_split)
		terminate(ERR_MEM);
	ft_get_splits(str_split, str, sep);
	ft_remove_char(str_split[0], '\"', 1);
	ft_remove_char(str_split[0], '\'', 1);
	return (str_split);
}
