/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 22:43:28 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/16 11:26:06 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	handle_exit_status_expansion(
			int last_exit_status, char **expanded_line,
			size_t *expanded_line_index, size_t *line_index);
void	handle_environment_variable_expansion(
			const char *line, size_t *line_index,
			char **expanded_line, size_t *expanded_line_index);
void	expand_line(char *line, int last_exit_status, char *expanded_line);
char	*get_local_env_var_value_from_name(char *name);

char	*do_expansions(char *line, int last_exit_status)
{
	char	*expanded_line;

	expanded_line = ft_calloc(calculate_expanded_line_length(
				line, last_exit_status) + 2, sizeof(char));
	if (!expanded_line)
	{	
		ft_cautious_free((void **)line);
		handle_error(NULL, 0);
		return (NULL);
	}
	expand_line(line, last_exit_status, expanded_line);
	ft_cautious_free((void **)&line);
	return (expanded_line);
}

void	expand_line(char *line, int last_exit_status, char *expanded_line)
{
	size_t	line_index;
	size_t	expanded_line_index;
	bool	ignore;

	ignore = false;
	expanded_line_index = 0;
	line_index = 0;
	while (line_index < ft_strlen(line))
	{
		if (line[line_index] == '\'')
		{
			ignore = !ignore;
			expanded_line[expanded_line_index++] = line[line_index++];
		}
		else if (line[line_index] == '$' && line[line_index + 1] == '?'
			&& !ignore)
			handle_exit_status_expansion(last_exit_status, &expanded_line,
				&expanded_line_index, &line_index);
		else if (line[line_index] == '$' && !ignore && (line[line_index + 1] \
			== '_' || ft_isalpha(line[line_index + 1])))
			handle_environment_variable_expansion(line, &line_index,
				&expanded_line, &expanded_line_index);
		else
			expanded_line[expanded_line_index++] = line[line_index++];
	}
}

void	handle_exit_status_expansion(
			int last_exit_status, char **expanded_line,
			size_t *expanded_line_index, size_t *line_index)
{
	char	*exit_status;
	size_t	exit_status_length;

	exit_status = ft_itoa(last_exit_status);
	exit_status_length = ft_strlen(exit_status);
	ft_memcpy(*expanded_line + *expanded_line_index, exit_status,
		exit_status_length);
	*expanded_line_index += exit_status_length;
	*line_index += 2;
	ft_cautious_free((void **)&exit_status);
}

void	handle_environment_variable_expansion(
			const char *line, size_t *line_index,
			char **expanded_line, size_t *expanded_line_index)
{
	char	*name;
	size_t	name_length;
	char	*value;
	size_t	value_length;

	(*line_index)++;
	name_length = get_variable_name_length(line, *line_index);
	name = ft_calloc(name_length + 1, sizeof(char));
	get_variable_name(line, *line_index, name);
	value = get_local_env_var_value_from_name(name);
	if (value != NULL)
	{
		value_length = ft_strlen(value);
		ft_memcpy(*expanded_line + *expanded_line_index, value, value_length);
		*expanded_line_index += value_length;
	}
	(*line_index) += name_length;
	ft_cautious_free((void **)&name);
}
