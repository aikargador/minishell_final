/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_room.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:04:16 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/18 18:27:51 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

extern t_command_table	g_command_table;

// not used until now, maybe useful in executor?
void	terminate_minishell(int exit_status, char *error_message)
{
	if (errno)
		perror("Shell");
	else if (error_message)
		ft_putstr_fd(error_message, STDERR_FILENO);
	free_command_table();
	exit(exit_status);
}

// Prints error message and frees the command table.
void	handle_error(char *error_message, int custom_errno)
{
	if (custom_errno)
		g_command_table.exit_status = custom_errno;
	else
		g_command_table.exit_status = errno;
	if (error_message)
		ft_putstr_fd(error_message, STDERR_FILENO);
	else if (errno)
		perror("Shell");
	free_command_table();
}
