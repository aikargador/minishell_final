/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_literal_interpretation_indicators.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:17:04 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/16 10:34:59 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

char	*remove_literal_interpretation_indicators_from_token(char *string,
			char c, char d);

void	remove_literal_interpretation_indicators_from_commands(
			t_command *commands)
{
	size_t	commands_index;
	size_t	arguments_index;

	commands_index = 0;
	while (commands[commands_index].name)
	{
		commands[commands_index].name
			= remove_literal_interpretation_indicators_from_token
			(commands[commands_index].name, '\'', '\"');
		arguments_index = 0;
		while (commands[commands_index].arguments[arguments_index])
		{
			commands
			[commands_index].arguments[arguments_index]
				= remove_literal_interpretation_indicators_from_token
				(commands[commands_index].arguments[arguments_index],
					'\'', '\"');
			arguments_index++;
		}
		commands_index++;
	}
}

void	handle_character_to_be_removed(char *string, size_t *old_index,
			size_t *new_index, char c)
{
	(*old_index)++;
	if (string[*old_index] == c
		&& (*old_index > 1 && ft_isspace(string[*old_index - 2])))
	{
		string[(*new_index)++] = EMPTY_TOKEN_INDICATOR;
		(*old_index)++;
		return ;
	}
	while (string[*old_index] && string[*old_index] != c)
	{
		string[(*new_index)++] = string[(*old_index)++];
	}
	if (string[*old_index] == c)
		(*old_index)++;
}

char	*remove_literal_interpretation_indicators_from_token(
			char *string, char c, char d)
{
	size_t	old_index;
	size_t	new_index;
	char	*old_string;

	if (!string || !string[0] || !string[1])
		return (string);
	old_string = string;
	string = ft_strtrim(string, " \t\r\v\f");
	free(old_string);
	old_index = 0;
	new_index = 0;
	while (string[old_index])
	{
		if (string[old_index] == c)
			handle_character_to_be_removed(string, &old_index, &new_index, c);
		if (string[old_index] == d)
			handle_character_to_be_removed(string, &old_index, &new_index, d);
		if (string[old_index] && (string[old_index] != c)
			&& (string[old_index] != d))
			string[new_index++] = string[old_index];
		if (string[old_index])
			old_index++;
	}
	string[new_index] = '\0';
	return (string);
}
