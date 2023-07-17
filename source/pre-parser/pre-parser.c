/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre-parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:17:19 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/18 18:16:38 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	has_unclosed_quotes(char *line);
bool	has_wrong_redirection(char *line, char redirection_char,
			char opposite_redirection_char);
bool	has_lonely_redirection_symbol(char *line);

bool	is_empty_line(char *line)
{
	size_t	index;

	if (!line[0])
		return (true);
	index = 0;
	add_history(line);
	while (line[index])
	{
		if (!ft_isspace(line[index]))
			return (false);
		index++;
	}
	return (true);
}

bool	has_syntax_error(char *line)
{
	if (has_unclosed_quotes(line))
		return (true);
	if (has_wrong_redirection(line, '>', '<'))
		return (true);
	if (has_wrong_redirection(line, '<', '>'))
		return (true);
	if (has_lonely_redirection_symbol(line))
		return (true);
	return (false);
}
