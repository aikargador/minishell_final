/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 21:29:44 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/16 23:50:26 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h> // for test

char	**line_into_tokens(char *line)
{
	char	**tokens;
	char	separators[7];

	line = separate_special_tokens(line);
	mask_whitespaces_to_be_ignored(line);
	fill_separators(separators);
	tokens = ft_split_charset(line, separators);
	unmask_ignored_whitespaces(tokens);
	ft_cautious_free((void **)&line);
	return (tokens);
}
