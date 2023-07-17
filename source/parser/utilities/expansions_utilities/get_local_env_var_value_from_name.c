/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_local_env_var_value_from_name.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 00:26:44 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/18 20:32:25 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"
#include <stdint.h>

extern t_command_table	g_command_table;

char	*get_local_env_var_value_from_name(char *name)
{
	t_env	*searching_ptr;

	if (!g_command_table.env_lst)
		return (NULL);
	searching_ptr = *(g_command_table.env_lst);
	while (searching_ptr)
	{
		if (ft_strncmp(name, searching_ptr->name, SIZE_MAX) == 0)
			return (searching_ptr->vals);
		searching_ptr = searching_ptr->nxt;
	}
	if (!ft_strncmp(name, "TERM", 5))
		if (g_command_table.dumb)
			return ("dumb");
	return (NULL);
}
