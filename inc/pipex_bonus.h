/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:33:44 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/21 18:35:04 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/* split_bonus.c */

char	**ft_split_mod(const char *str, const char *sep);

/* process_argv_bonus.c */

int		ft_process_argv(char *argv, char ***argv_split, char **command,
			char *env[]);

#endif
