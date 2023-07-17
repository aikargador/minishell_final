/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:56:38 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/19 02:08:36 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

extern t_command_table	g_command_table;

void	free_command_table(void)
{
	t_env	**env_lst;

	if (g_command_table.commands)
		free_commands(&(g_command_table.commands));
	env_lst = g_command_table.env_lst;
	g_command_table = (t_command_table){0};
	g_command_table.env_lst = env_lst;
}
