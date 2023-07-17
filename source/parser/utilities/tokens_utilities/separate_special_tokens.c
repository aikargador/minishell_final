/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_special_tokens.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 00:15:00 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/19 02:37:11 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "../../../../libft/libft.h"
#include <stdio.h> // debug

void	handle_quote(bool *quote_flag, char *old_string,
			char *new_string, size_t *index)
{
	*quote_flag = !(*quote_flag);
	ft_strncat(new_string, &old_string[*index], 1);
	(*index)++;
}

void	generate_spaced_string(char *old_string, char *new_string,
			size_t new_string_size, char c)
{
	size_t	index;
	bool	inside_single_quote;
	bool	inside_double_quote;

	inside_single_quote = false;
	inside_double_quote = false;
	index = 0;
	while (old_string[index])
	{
		if ((old_string[index] == '\'' && !inside_double_quote))
			handle_quote(&inside_single_quote, old_string, new_string, &index);
		if ((old_string[index] == '"' && !inside_single_quote))
			handle_quote(&inside_double_quote, old_string, new_string, &index);
		if ((!inside_single_quote && !inside_double_quote
				&& old_string[index] == c)
			&& (index == 0 || old_string[index - 1] != c))
			ft_strlcat(new_string, " ", new_string_size);
		ft_strncat(new_string, &old_string[index], 1);
		if ((!inside_single_quote && !inside_double_quote && old_string[index]
				== c) && (index == ft_strlen(old_string) - 1
				|| old_string[index + 1] != c))
			ft_strlcat(new_string, " ", new_string_size);
		index++;
	}
}

char	*add_spaces(char *haystack, char c)
{
	int		haystack_length;
	char	*new_string;

	if (!haystack || !(haystack[0]) || !(haystack[1]))
		return (haystack);
	haystack_length = ft_strlen(haystack);
	new_string = ft_calloc(haystack_length * 3 + 1, sizeof(char));
	generate_spaced_string(haystack, new_string, haystack_length * 3 + 1, c);
	return (new_string);
}

char	*separate_special_tokens(char *line)
{
	char	*new_line;

	if (line[0] && !line[1])
		return (line);
	new_line = add_spaces(line, '<');
	ft_cautious_free((void **)&line);
	line = new_line;
	new_line = add_spaces(line, '>');
	ft_cautious_free((void **)&line);
	line = new_line;
	new_line = add_spaces(line, '|');
	ft_cautious_free((void **)&line);
	return (new_line);
}
