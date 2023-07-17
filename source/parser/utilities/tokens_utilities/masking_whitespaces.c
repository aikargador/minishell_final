/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   masking_whitespaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 00:16:32 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/10 00:43:18 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "../../../../libft/libft.h"

// The amount added to each white-space type character to mask them from-
// ft_split. 5 may look arbitrary but its just enough to-
// turn white-space type chracters into non-white-space type characters.
#define MASKED_SPACE -2
#define MASKED_TAB -3
#define MASKED_NEW_LINE -4
#define MASKED_VERTICAL_TAB -5
#define MASKED_FORM_FEED -6
#define MASKED_CARRIAGE_RETURN -7

char	get_masked(char whitespace)
{
	if (whitespace == ' ')
		return (MASKED_SPACE);
	else if (whitespace == '\t')
		return (MASKED_TAB);
	else if (whitespace == '\n')
		return (MASKED_NEW_LINE);
	else if (whitespace == '\r')
		return (MASKED_CARRIAGE_RETURN);
	else if (whitespace == '\f')
		return (MASKED_FORM_FEED);
	else if (whitespace == '\v')
		return (MASKED_VERTICAL_TAB);
	return (whitespace);
}

void	mask_whitespaces_to_be_ignored(char *line)
{
	size_t	line_index;
	bool	ignore_single_quote;
	bool	ignore_double_quote;

	ignore_single_quote = false;
	ignore_double_quote = false;
	line_index = 0;
	while (line[line_index])
	{
		if (line[line_index] == '\'' && !ignore_double_quote)
			ignore_single_quote = !ignore_single_quote;
		else if ((line[line_index] == '\"' && !ignore_single_quote))
			ignore_double_quote = !ignore_double_quote;
		else if (ft_isspace(line[line_index])
			&& (ignore_single_quote || ignore_double_quote))
			line[line_index] = get_masked(line[line_index]);
		line_index++;
	}
}

char	get_unmasked(signed char masked_whitespace)
{
	if (masked_whitespace == MASKED_SPACE)
		return (' ');
	else if (masked_whitespace == MASKED_TAB)
		return ('\t');
	else if (masked_whitespace == MASKED_CARRIAGE_RETURN)
		return ('\r');
	else if (masked_whitespace == MASKED_FORM_FEED)
		return ('\f');
	else if (masked_whitespace == MASKED_VERTICAL_TAB)
		return ('\v');
	else if (masked_whitespace == MASKED_NEW_LINE)
		return ('\n');
	return (masked_whitespace);
}

bool	is_masked(signed char character)
{
	if (character >= MASKED_CARRIAGE_RETURN && character <= MASKED_SPACE)
		return (true);
	else
		return (false);
}

void	unmask_ignored_whitespaces(char **tokens)
{
	size_t	token_index;
	size_t	tokens_index;

	tokens_index = 0;
	if (!tokens)
		return ;
	while (tokens[tokens_index])
	{
		token_index = 0;
		while (tokens[tokens_index][token_index])
		{
			if (is_masked(tokens[tokens_index][token_index]))
				tokens[tokens_index][token_index]
					= get_unmasked(tokens[tokens_index][token_index]);
			token_index++;
		}
		tokens_index++;
	}
}
