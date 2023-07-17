/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_string_length_calculator.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 23:22:25 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/18 16:40:40 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "../../../../libft/libft.h"

void	get_variable_name(const char *line, size_t index,
			char *name);
size_t	get_variable_name_length(const char *line, size_t index);
void	handle_environment_variable(const char *line, size_t *index,
			size_t *length);
void	handle_exit_status(size_t *length, int last_exit_status,
			size_t *index);
char	*get_local_env_var_value_from_name(char *name);

size_t	calculate_expanded_line_length(const char *line, int last_exit_status)
{
	size_t	length;
	bool	ignore;
	size_t	line_index;

	length = 0;
	ignore = false;
	line_index = 0;
	while (line_index < ft_strlen(line))
	{
		if (line[line_index] == '\'')
		{
			ignore = !ignore;
			length++;
		}
		else if (line[line_index] == '$' && line[line_index + 1] == '?'
			&& !ignore)
			handle_exit_status(&length, last_exit_status, &line_index);
		else if (line[line_index] == '$' && !ignore && (line[line_index + 1] \
				== '_' || ft_isalpha(line[line_index + 1])))
			handle_environment_variable(line, &line_index, &length);
		else
			length++;
		line_index++;
	}
	return (length);
}

void	handle_exit_status(size_t *length, int last_exit_status, size_t *index)
{
	(*length) += ft_get_signed_number_length(last_exit_status);
	(*index)++;
}

void	handle_environment_variable(const char *line, size_t *index,
			size_t *length)
{
	char	*name;
	size_t	name_length;
	char	*value;

	name_length = get_variable_name_length(line, (*index) + 1);
	name = ft_calloc(name_length + 1, sizeof(char));
	get_variable_name(line, (*index) + 1, name);
	value = get_local_env_var_value_from_name(name);
	if (value != NULL)
		*length += ft_strlen(value);
	ft_cautious_free((void **)&name);
	(*index) += name_length;
}

size_t	get_variable_name_length(const char *line, size_t line_index)
{
	size_t	length;

	length = 0;
	while ((ft_isalnum(line[line_index]) || line[line_index] == '_'))
	{
		length++;
		line_index++;
	}
	return (length);
}

void	get_variable_name(const char *line, size_t line_index,
			char *variable_identifier_target)
{
	int	variable_index;

	variable_index = 0;
	while (ft_isalnum(line[line_index]) || line[line_index] == '_')
	{
		variable_identifier_target[variable_index++] = line[line_index++];
	}
	variable_identifier_target[variable_index] = 0;
}
