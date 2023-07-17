/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_command_table.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:54:31 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/18 18:03:42 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

extern t_command_table	g_command_table;

void	remove_empty_strings(char **strings)
{
	int	read_index;
	int	write_index;

	if (strings == NULL)
		return ;
	read_index = 0;
	write_index = 0;
	while (strings[read_index] != NULL)
	{
		if (strings[read_index][0] != '\0')
		{
			if (read_index != write_index)
			{
				strings[write_index] = strings[read_index];
			}
			write_index++;
		}
		else
		{
			free(strings[read_index]);
			strings[read_index] = NULL;
		}
		read_index++;
	}
	strings[write_index] = NULL;
}

void	clean_command_table(void)
{
	size_t	index;

	if (!g_command_table.commands)
		return ;
	index = 0;
	while (g_command_table.commands[index].name)
	{
		remove_empty_strings(g_command_table.commands[index].arguments);
		index++;
	}
}
