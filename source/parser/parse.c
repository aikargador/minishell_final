/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 21:20:37 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/18 17:48:27 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_command	*parse(char *line, int last_exit_status)
{
	t_command		*commands;
	char			**tokens;
	bool			status;

	commands = NULL;
	mask_solitary_quotes(line);
	mask_heredoc_dollar_signs(line);
	line = do_expansions(line, last_exit_status);
	unmask_heredoc_dollar_signs(line);
	if (!line)
		return (NULL);
	tokens = line_into_tokens(line);
	commands = tokens_into_commands(tokens);
	if (!commands)
		return (commands);
	status = encode_redirections(commands);
	if (!status)
		return (NULL);
	unmask_solitary_quotes(commands);
	status = handle_heredoc_redirections(commands);
	if (!status)
		return (NULL);
	remove_literal_interpretation_indicators_from_commands(commands);
	return (commands);
}
