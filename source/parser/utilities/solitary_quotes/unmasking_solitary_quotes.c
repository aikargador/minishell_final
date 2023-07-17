/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unmasking_solitary_quotes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:57:40 by oaydemir          #+#    #+#             */
/*   Updated: 2023/01/30 17:00:30 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "../../../../libft/libft.h"
#include "../../parser.h"

#define SINGLE_QUOTE_MASKING_VALUE -55
#define DOUBLE_QUOTE_MASKING_VALUE -56

void	unmask_command_name(t_command *commands)
{
	size_t	commands_index;
	size_t	name_index;

	commands_index = 0;
	while (commands[commands_index].name)
	{
		name_index = 0;
		while (commands[commands_index].name[name_index])
		{
			if ((signed char)commands[commands_index].name[name_index]
				== SINGLE_QUOTE_MASKING_VALUE)
				commands[commands_index].name[name_index] = '\'';
			else if ((signed char)commands[commands_index].name[name_index]
				== DOUBLE_QUOTE_MASKING_VALUE)
				commands[commands_index].name[name_index] = '\"';
			name_index++;
		}
		commands_index++;
	}
}

void	unmask_argument(t_command *commands, size_t commands_index,
			size_t arguments_index)
{
	size_t	argument_index;

	argument_index = 0;
	while (commands[commands_index].arguments[arguments_index][argument_index])
	{
		if ((signed char)commands[commands_index].arguments \
			[arguments_index][argument_index] == SINGLE_QUOTE_MASKING_VALUE)
			commands[commands_index]. \
				arguments[arguments_index][argument_index] = '\'';
		else if ((signed char)commands[commands_index].arguments \
			[arguments_index][argument_index] == DOUBLE_QUOTE_MASKING_VALUE)
			commands[commands_index]. \
				arguments[arguments_index][argument_index] = '\"';
		argument_index++;
	}
}

void	unmask_command_arguments(t_command *commands)
{
	size_t	commands_index;
	size_t	arguments_index;

	commands_index = 0;
	while (commands[commands_index].name)
	{
		if (!commands[commands_index].arguments)
		{
			commands_index++;
			continue ;
		}
		arguments_index = 0;
		while (commands[commands_index].arguments[arguments_index])
		{
			unmask_argument(commands, commands_index, arguments_index);
			arguments_index++;
		}
		commands_index++;
	}
}

void	unmask_solitary_quotes(t_command *commands)
{
	if (!commands)
		return ;
	unmask_command_name(commands);
	unmask_command_arguments(commands);
}
