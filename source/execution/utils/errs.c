/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:50:33 by aikram            #+#    #+#             */
/*   Updated: 2023/03/11 14:30:29 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	ret_perr(char *str)
{
	perror(str);
	return (EXIT_FAILURE);
}

int	msg_err(char *str, int ret_val)
{
	ft_putstr_fd(str, 2);
	return (ret_val);
}
