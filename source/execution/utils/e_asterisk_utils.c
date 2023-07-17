/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_asterisk_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:46:02 by aikram            #+#    #+#             */
/*   Updated: 2023/03/18 18:15:27 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	chk_exit_arg(t_tbl *tbl, t_exe *ex)
{
	int	i;
	int	non_numeric;

	i = 0;
	non_numeric = 0;
	if (tbl->commands[ex->i].arguments[0])
	{
		if (tbl->commands[ex->i].arguments[0][i] == '-')
			i++;
		while (tbl->commands[ex->i].arguments[0][i] && !non_numeric)
		{
			if (!ft_isdigit(tbl->commands[ex->i].arguments[0][i]) &&
				tbl->commands[ex->i].arguments[0][i] != ' ')
					non_numeric = 1;
			i++;
		}
		if (!non_numeric && tbl->commands[ex->i].arguments[0])
		{
			giga_chad_atoi(tbl->commands[ex->i].arguments[0], ex);
			if (ex->bad_no)
				non_numeric = 1;
		}
	}
	return (non_numeric);
}

int	exit_util(t_tbl *tbl, t_exe *ex, char *err)
{
	if (tbl->commands[ex->i].arguments[0])
	{
		if (*tbl->commands[ex->i].arguments[0])
		{
			if (tbl->commands[ex->i].arguments[1])
			{
				if (*tbl->commands[ex->i].arguments[1])
				{
					err = ft_strjoin("minishell: exit", ERR_TAG);
					msg_err(err, 1);
					free(err);
					tbl->exit = false;
					return (1);
				}
			}
		}
	}
	return (0);
}

int	echo_utils(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] == 'n')
		i++;
	if (!str[i])
		return (1);
	printf("%s", str);
	return (0);
}
