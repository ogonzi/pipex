/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_argv.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:02:59 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/11 09:35:50 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_ARGV_H
# define PROCESS_ARGV_H

void	ft_process_argv(char *argv, char ***argv_split, char **command,
			char *env[]);

#endif
