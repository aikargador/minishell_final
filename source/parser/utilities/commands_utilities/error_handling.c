/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:43:17 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/18 17:47:37 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"
#include <stdint.h>

void	free_previously_allocated_memory(
			t_command *commands, size_t *commands_index)
{
	size_t	index;

	index = 0;
	while (commands[*commands_index].arguments[index])
	{
		free(commands[*commands_index].arguments[index]);
		index++;
	}
	free(commands[*commands_index].arguments);
}

bool	handle_error_local(char **tokens)
{
	ft_free_string_array(&tokens);
	handle_error(NULL, 0);
	return (false);
}

void	handle_empty_command_arguments(char **command_name)
{
	(*command_name)[0] = '\0';
}
