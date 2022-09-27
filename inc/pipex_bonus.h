/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:33:44 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/27 16:53:33 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/* split_bonus.c */

char	**ft_split_mod(const char *str, const char *sep);

/* process_argv_bonus.c */

int		ft_process_argv(char *argv, char ***argv_split, char **command,
			char *env[]);

/* remove_char.c */

void	ft_remove_char(char *str, char char_to_remove, int first_and_last);

#endif
