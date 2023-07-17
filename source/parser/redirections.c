/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 20:03:54 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/18 17:47:49 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	encode_redirections_in_command(t_command *command);
bool	add_redirection(t_redirect_info *redirect_info,
			char *redirection_symbol, char *filename_or_delimiter);
bool	is_redirection_symbol(char *token);
bool	is_filled_string(char *string);
bool	handle_command_name_redirection(char **command_name,
			char **command_arguments, t_redirect_info *redirect_info);
bool	handle_command_argument_redirection(char *argument,
			char *next_argument, t_redirect_info *redirect_info);
void	handle_empty_command_arguments(char **command_name);

bool	encode_redirections(t_command *commands)
{
	size_t	commands_index;
	bool	status;

	commands_index = 0;
	while (commands[commands_index].name || commands[commands_index].arguments)
	{
		status = encode_redirections_in_command(&(commands[commands_index]));
		if (!status)
			return (false);
		commands_index++;
	}
	return (true);
}

bool	encode_redirections_in_command(t_command *command)
{
	size_t			index;

	index = 0;
	if (command->name && is_redirection_symbol(command->name))
	{
		if (!handle_command_name_redirection(
				&(command->name), command->arguments,
				&(command->redirect_info)))
			return (false);
	}
	while (is_filled_string(command->arguments[index])
		&& is_filled_string(command->arguments[index + 1]))
	{
		if (is_redirection_symbol(command->arguments[index]))
		{
			if (!handle_command_argument_redirection(command->arguments[index],
					command->arguments[index + 1], &(command->redirect_info)))
				return (false);
			index += 2;
		}
		else
			index++;
	}
	return (true);
}

void	replace_command_name(char **command_name, char **command_arguments)
{
	size_t	index;

	if (!command_arguments)
		return (handle_empty_command_arguments(command_name));
	index = 0;
	while (command_arguments[index])
	{
		if (is_redirection_symbol(command_arguments[index])
			&& command_arguments[index + 1])
		{
			if (command_arguments[index + 1])
				index += 2;
			else
				index++;
		}
		else
		{
			*command_name = ft_strdup(command_arguments[index]);
			command_arguments[index][0] = '\0';
			return ;
		}
	}
	(*command_name)[0] = '\0';
}

bool	handle_command_name_redirection(char **command_name,
			char **command_arguments, t_redirect_info *redirect_info)
{
	bool	status;

	if (!command_arguments || !command_arguments[0]
		|| is_redirection_symbol(command_arguments[0]))
	{
		handle_error("syntax error near unexpected token.\n", 0);
		return (false);
	}
	status = add_redirection(redirect_info, *command_name,
			ft_strdup(command_arguments[0]));
	if (!status)
		return (false);
	replace_command_name(command_name, command_arguments);
	return (true);
}

bool	handle_command_argument_redirection(char *argument,
			char *next_argument, t_redirect_info *redirect_info)
{
	bool	status;

	if (is_redirection_symbol(next_argument)
		|| !next_argument)
	{
		handle_error("syntax error near unexpected token.\n", 0);
		return (false);
	}
	status = add_redirection(redirect_info,
			argument, ft_strdup(next_argument));
	if (!status)
		return (false);
	argument[0] = '\0';
	next_argument[0] = '\0';
	return (true);
}
