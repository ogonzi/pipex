/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:52:19 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/27 16:52:24 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_search_first(char *str, int len, char char_to_remove)
{
	int	i;

	i = -1;
	while (++i < len)
		if (str[i] == char_to_remove)
			return (i);
	return (-1);
}

int	ft_search_last(char *str, int len, char char_to_remove)
{
	int	i;

	i = len;
	while (--i >= 0)
	{
		if (str[i] == char_to_remove)
			return (i);
	}
	return (-1);
}

void	ft_remove_sequence(int *i, int *j, int *len, char **str)
{
	*j = *i - 1;
	while (++(*j) < *len)
		(*str)[*j] = (*str)[*j + 1];
	(*len)--;
	(*i)--;
}

void	ft_remove_char(char *str, char char_to_remove, int first_and_last)
{
	int	i;
	int	j;
	int	len;
	int	first;
	int	last;

	len = ft_strlen(str);
	first = ft_search_first(str, len, char_to_remove);
	last = ft_search_last(str, len, char_to_remove);
	i = -1;
	while (++i < len)
	{
		if (str[i] == char_to_remove)
		{
			if (first_and_last == 0)
				ft_remove_sequence(&i, &j, &len, &str);
			else if (i == first || i == last - 1)
				ft_remove_sequence(&i, &j, &len, &str);
		}
	}
}
