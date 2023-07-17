/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:11:46 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/18 17:48:42 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "parser.h"

size_t		count_commands(char **tokens);
size_t		count_command_arguments(char **tokens);
bool		fill_command_name(t_command *commands, size_t *commands_index,
				size_t *tokens_index, char **tokens);
bool		fill_command_arguments(
				t_command *commands, size_t *commands_index,
				size_t *tokens_index, char **tokens);
t_command	*allocate_memory_for_commands(char **tokens);

t_command	*tokens_into_commands(char **tokens)
{
	t_command	*commands;
	size_t		tokens_i;
	size_t		commands_i;
	size_t		number_of_commands;

	number_of_commands = count_commands(tokens);
	if (number_of_commands == SIZE_MAX || number_of_commands == 0)
		return (NULL);
	commands = allocate_memory_for_commands(tokens);
	if (!commands)
		return (NULL);
	commands_i = 0;
	tokens_i = 0;
	while (commands_i < number_of_commands)
	{
		if (!fill_command_name(commands, &commands_i, &tokens_i, tokens))
			return (NULL);
		if (!fill_command_arguments(commands, &commands_i, &tokens_i, tokens))
			return (NULL);
		commands_i++;
		tokens_i++;
	}
	ft_free_string_array(&tokens);
	return (commands);
}

void	free_command(t_command command)
{
	size_t	arguments_index;

	ft_cautious_free((void **)&(command.name));
	arguments_index = 0;
	while (command.arguments[arguments_index])
	{
		ft_cautious_free((void **)&(command
				.arguments[arguments_index]));
		arguments_index++;
	}
	ft_cautious_free((void **)&(command.arguments));
	ft_cautious_free((void **)&(command
			.redirect_info.redirect_input_source_filename));
	ft_cautious_free((void **)&(command.redirect_info.heredoc_delimiter));
	ft_cautious_free((void **)&(command
			.redirect_info.redirect_output_target_filename));
}

void	free_commands(t_command **commands_ptr)
{
	t_command	*commands;
	size_t		commands_index;

	commands_index = 0;
	if (!commands_ptr || !(*commands_ptr))
		return ;
	commands = *commands_ptr;
	while (commands[commands_index].name != NULL)
	{
		free_command(commands[commands_index]);
		commands_index++;
	}
	ft_cautious_free((void **)commands_ptr);
}
