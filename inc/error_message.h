/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:48:53 by ogonzale          #+#    #+#             */
/*   Updated: 2022/08/13 12:36:17 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGE_H
# define ERROR_MESSAGE_H

# define ERR_ARGS	"Incorrect number of arguments, expected 5"
# define ERR_OPEN	"Error opening the file"
# define ERR_READ	"Error reading the file"
# define ERR_WRITE	"Error writing to a file"
# define ERR_PIPE	"Error creating pipe"
# define ERR_FORK	"Error forking process"
# define ERR_MEM	"Error allocating memory"
# define ERR_EXEC	"Error executing command"
# define ERR_DUP	"Error duplicating a file descriptor" 
# define ERR_CLOSE	"Error closing a file descriptor"
# define ERR_WAIT	"Error waiting for a process to change state"
# define ERR_QUOTES	"Opening quotes aren't properly closed"

#endif
