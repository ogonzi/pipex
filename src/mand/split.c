/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:00:14 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/12 12:24:34 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "error_message.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_skip_quoted(const char *str, int *i, char c)
{
	if (str[*i] == c)
	{
		(*i)++;
		while (str[*i] != c)
		{
			if (str[*i] == '\0')
				terminate(ERR_QUOTES);
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
			if (!str_split[j])
				terminate(ERR_MEM);
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
	return (str_split);
}
