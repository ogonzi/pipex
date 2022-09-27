/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:37:34 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/27 17:38:01 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* split.c */

char	**ft_split_mod(const char *str, const char *sep);

/* process_argv.c */

int		ft_process_argv(char *argv, char ***argv_split, char **command,
			char *env[]);

/* remove_char.c */

void	ft_remove_char(char *str, char char_to_remove, int first_and_last);

#endif
