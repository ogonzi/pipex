/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:08:03 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/15 15:08:33 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_remove_char(char *str, char char_to_remove)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(str);
	i = -1;
	while (++i < len)
	{
		if (str[i] == char_to_remove)
		{
			j = i - 1;
			while (++j < len)
				str[j] = str[j + 1];
			len--;
			i--;
		}
	}
}
