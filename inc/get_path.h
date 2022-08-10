/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:02:59 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/10 17:52:25 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_PATH_H
# define GET_PATH_H

void	ft_get_command(char **cmd, char **opt, char *argv_cmd, char *env[]);
void    ft_fill_args_cmd(char *cmd, char *options, char ***args_cmd);
#endif
