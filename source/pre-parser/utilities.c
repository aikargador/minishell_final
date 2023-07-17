/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:01:28 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/19 01:34:02 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "../minishell.h"

bool	check_through_quote(char *line, size_t *index, char quote)
{
	(*index)++;
	while (line[*index] && line[*index] != quote)
		(*index)++;
	if (line[*index] == quote)
		(*index)++;
	else if (!line[*index])
		return (true);
	return (false);
}

bool	has_unclosed_quotes(char *line)
{
	size_t	index;
	bool	status;

	status = false;
	index = 0;
	while (line[index])
	{
		if (line[index] == '\'')
		{
			status = check_through_quote(line, &index, '\'');
			if (status == true)
				return (status);
		}
		if (line[index] == '"')
		{
			status = check_through_quote(line, &index, '"');
			if (status == true)
				return (status);
		}
		if (line[index] && line[index] != '\'' && line[index] != '"')
			index++;
	}
	return (status);
}

bool	is_wrong_redirection(char *line, size_t *i,
			char redir_char, char opposite_redir_char)
{
	(*i)++;
	while (line[(*i)] && (line[(*i)] == '\'' || line[(*i)] == '"'))
		(*i)++;
	if (line[(*i)] == opposite_redir_char || line[(*i)] == redir_char)
		return (true);
	return (false);
}

bool	has_wrong_redirection(char *line, char redir_char,
			char opposite_redir_char)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			check_through_quote(line, &i, '\'');
		else if (line[i] == '"')
			check_through_quote(line, &i, '"');
		else if (line[i] == redir_char)
		{
			i++;
			while (line[i] && (line[i] == '\'' || line[i] == '"'))
				i++;
			if (line[i] == opposite_redir_char)
				return (true);
			else if (line[i] == redir_char && is_wrong_redirection(
					line, &i, redir_char, opposite_redir_char))
				return (true);
		}
		else
			i++;
	}
	return (false);
}

bool	has_lonely_redirection_symbol(char *line)
{
	size_t	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == '\'')
			check_through_quote(line, &index, '\'');
		else if (line[index] == '"')
			check_through_quote(line, &index, '"');
		else if (line[index] == '>' || line[index] == '<' || line[index] == '|')
		{
			index++;
			while (line[index] && ft_isspace(line[index]))
				index++;
			if (!line[index] || line[index] == '|')
				return (true);
		}
		else
			index++;
	}
	return (false);
}
