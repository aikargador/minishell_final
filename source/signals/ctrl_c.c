/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:27:14 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/19 00:20:45 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "../../libft/libft.h"
#include "../minishell.h"

extern t_command_table	g_command_table;

void	ctrl_c_handler(int signal_num)
{
	if (g_command_table.child_pid > 0)
	{
		g_command_table.child_pid = 0;
	}
	g_command_table.exit_status = 1;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)signal_num;
}
