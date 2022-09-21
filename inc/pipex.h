/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:01:23 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/21 18:19:55 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* split.c */

char	**ft_split_mod(const char *str, const char *sep);

/* process_argv.c */

int		ft_process_argv(char *argv, char ***argv_split, char **command,
			char *env[]);

#endif
