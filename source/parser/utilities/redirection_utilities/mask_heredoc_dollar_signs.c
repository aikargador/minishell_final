/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask_heredoc_dollar_signs.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:03:55 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/18 16:39:31 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../parser.h"

void	mask_heredoc_dollar_signs(char *line)
{
	while (line)
	{
		line = ft_strnstr(line, "<<", ft_strlen(line));
		if (line && *line)
			line += 2;
		else
			continue ;
		while (line && *line && ft_isspace(*line))
			line++;
		while (line && *line && !ft_isspace(*line))
		{
			if (*line == '$')
				*line = (signed char)MASKED_DOLLAR_SIGN;
			line++;
		}
	}
}

void	unmask_heredoc_dollar_signs(char *line)
{
	size_t	index;

	index = 0;
	while (line[index])
	{
		if ((signed char)line[index] == MASKED_DOLLAR_SIGN)
			line[index] = '$';
		index++;
	}
}
