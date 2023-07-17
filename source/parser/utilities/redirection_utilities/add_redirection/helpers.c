/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 23:26:07 by oaydemir          #+#    #+#             */
/*   Updated: 2023/02/26 14:56:06 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../parser.h"

bool	check_null_pointers(t_redirect_info *redirect_info,
		char *redirection_symbol, char *filename_or_delimiter)
{
	if (!redirect_info || !redirection_symbol || !filename_or_delimiter)
	{
		handle_error(NULL, 0);
		return (false);
	}
	return (true);
}

bool	is_redirection_symbol(char *token)
{
	if (!token)
		return (false);
	else if (ft_strncmp(token, ">", 2) == 0)
		return (true);
	else if (ft_strncmp(token, "<", 2) == 0)
		return (true);
	else if (ft_strncmp(token, ">>", 3) == 0)
		return (true);
	else if (ft_strncmp(token, "<<", 3) == 0)
		return (true);
	else
		return (false);
}

bool	is_filled_string(char *string)
{
	if (string && string[0])
		return (true);
	else
		return (false);
}
