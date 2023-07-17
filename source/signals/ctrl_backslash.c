/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_backslash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:21:57 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/19 00:21:02 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "../minishell.h"

extern t_command_table	g_command_table;

void	ctrl_backslash_handler(int signal_num)
{
	if (g_command_table.child_pid > 0)
	{
		g_command_table.child_pid = 0;
	}
	(void)signal_num;
}
