/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   masking_solitary_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:20:53 by oaydemir          #+#    #+#             */
/*   Updated: 2023/01/30 17:00:27 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "../../../../libft/libft.h"
#include "../../parser.h"

#define SINGLE_QUOTE_INDEX 0
#define DOUBLE_QUOTE_INDEX 1

#define SINGLE_QUOTE_MASKING_VALUE -55
#define DOUBLE_QUOTE_MASKING_VALUE -56

void	initialize_arrays(size_t **masked_quote_indices,
			size_t **masked_quote_counters)
{
	*masked_quote_counters = ft_calloc(2, sizeof(size_t));
	*masked_quote_indices = ft_calloc(2, sizeof(size_t));
	(void)masked_quote_counters;
}

void	handle_single_quote(char *line, size_t *line_index,
		size_t *masked_quote_indices, size_t *masked_quote_counters)
{
	masked_quote_indices[SINGLE_QUOTE_INDEX] = *line_index;
	masked_quote_counters[SINGLE_QUOTE_INDEX]++;
	(*line_index)++;
	while (line[*line_index] && line[*line_index] != '\'')
		(*line_index)++;
	if (!line[*line_index])
		*line_index = masked_quote_indices[SINGLE_QUOTE_INDEX] + 1;
	else
	{
		masked_quote_indices[SINGLE_QUOTE_INDEX] = *line_index;
		masked_quote_counters[SINGLE_QUOTE_INDEX]++;
		(*line_index)++;
	}
}

void	handle_double_quote(char *line, size_t *line_index,
		size_t *masked_quote_indices, size_t *masked_quote_counters)
{
	masked_quote_indices[DOUBLE_QUOTE_INDEX] = *line_index;
	masked_quote_counters[DOUBLE_QUOTE_INDEX]++;
	(*line_index)++;
	while (line[*line_index] && line[*line_index] != '\"')
		(*line_index)++;
	if (!line[*line_index])
		*line_index = masked_quote_indices[DOUBLE_QUOTE_INDEX] + 1;
	else
	{
		masked_quote_indices[DOUBLE_QUOTE_INDEX] = *line_index;
		masked_quote_counters[DOUBLE_QUOTE_INDEX]++;
		(*line_index)++;
	}
}

void	mask(char *line,
			size_t *masked_quote_indices, size_t *masked_quote_counters)
{
	if (masked_quote_counters[SINGLE_QUOTE_INDEX] % 2 == 1)
		line[masked_quote_indices[SINGLE_QUOTE_INDEX]]
			= (signed char)SINGLE_QUOTE_MASKING_VALUE;
	if (masked_quote_counters[DOUBLE_QUOTE_INDEX] % 2 == 1)
		line[masked_quote_indices[DOUBLE_QUOTE_INDEX]]
			= (signed char)DOUBLE_QUOTE_MASKING_VALUE;
}

void	mask_solitary_quotes(char *line)
{
	size_t	*masked_quote_indices;
	size_t	*masked_quote_counters;
	size_t	line_index;

	if (!line)
		return ;
	initialize_arrays(&masked_quote_indices, &masked_quote_counters);
	line_index = 0;
	while (line[line_index])
	{
		if (line[line_index] == '\'')
			handle_single_quote(line, &line_index,
				masked_quote_indices, masked_quote_counters);
		else if (line[line_index] == '\"')
			handle_double_quote(line, &line_index,
				masked_quote_indices, masked_quote_counters);
		else
			line_index++;
	}
	mask(line, masked_quote_indices, masked_quote_counters);
	free(masked_quote_counters);
	free(masked_quote_indices);
}
