/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utilities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 21:44:59 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/16 12:48:32 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"
#include <stdint.h>

void	free_previously_allocated_memory(
			t_command *commands, size_t *commands_index);
bool	handle_error_local(char **tokens);

t_command	*allocate_memory_for_commands(char **tokens)
{
	t_command	*commands;
	size_t		number_of_commands;

	number_of_commands = count_commands(tokens);
	commands = ft_calloc(number_of_commands + 1, sizeof(t_command));
	if (!commands)
	{
		ft_free_string_array(&tokens);
		handle_error(NULL, 0);
		return (NULL);
	}
	return (commands);
}

bool	fill_command_name(t_command *commands, size_t *commands_index,
			size_t *tokens_index, char **tokens)
{
	if (tokens[*tokens_index][0] == '|')
	{
		ft_free_string_array(&tokens);
		handle_error(NULL, 0);
		return (false);
	}
	commands[*commands_index].name = ft_strdup(tokens[*tokens_index]);
	if (commands[*commands_index].name == NULL)
	{
		ft_free_string_array(&tokens);
		handle_error(NULL, 0);
		return (false);
	}
	(*tokens_index)++;
	return (true);
}

bool	fill_command_arguments(t_command *commands, size_t *commands_index,
			size_t *tokens_index, char **tokens)
{
	size_t	command_arguments_index;

	commands[*commands_index].arguments = ft_calloc(count_command_arguments(
				&(tokens[*tokens_index])) + 1, sizeof(char *));
	if (!(commands[*commands_index].arguments))
		return (handle_error_local(tokens));
	command_arguments_index = 0;
	while (tokens[*tokens_index]
		&& (ft_strncmp(tokens[*tokens_index], "|", 1) != 0))
	{
		commands[*commands_index].arguments[command_arguments_index]
			= ft_strdup(tokens[*tokens_index]);
		if (!(commands[*commands_index].arguments[command_arguments_index]))
		{
			free_previously_allocated_memory(commands, commands_index);
			return (handle_error_local(tokens));
		}
		(*tokens_index)++;
		command_arguments_index++;
	}
	return (true);
}

size_t	count_commands(char **tokens)
{
	size_t	commands_count;
	size_t	tokens_index;

	commands_count = 1;
	tokens_index = 0;
	if (!tokens[tokens_index] || !tokens[tokens_index][0])
		return (0);
	while (tokens[tokens_index])
	{
		if (ft_strncmp(tokens[tokens_index], "|", 1) == 0)
			commands_count++;
		tokens_index++;
	}
	if (ft_strncmp(tokens[tokens_index - 1], "|", 1) == 0)
	{
		ft_free_string_array(&tokens);
		handle_error("minishell: syntax error near unexpected token \'|\'\n", 0);
		return (SIZE_MAX);
	}
	return (commands_count);
}

size_t	count_command_arguments(char **tokens)
{
	size_t	arguments_count;
	size_t	tokens_index;

	arguments_count = 0;
	tokens_index = 0;
	while (tokens[tokens_index]
		&& ft_strncmp(tokens[tokens_index], "|", 1) != 0)
	{
		arguments_count++;
		tokens_index++;
	}
	return (arguments_count);
}
