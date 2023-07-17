/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:31:18 by aikram            #+#    #+#             */
/*   Updated: 2023/03/19 08:37:03 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	chk_valid_env(t_exe *ex)
{
	int	i;

	i = -1;
	while (ex->ex_un[++i])
	{
		if (i == 0 && !(isalpha(ex->ex_un[i])) && ex->ex_un[i] != '_')
			return (err_msg_env(ex));
		else if (!(isalnum(ex->ex_un[i])) && ex->ex_un[i] != '_' \
			&& ex->ex_un[i + 1])
			return (err_msg_env(ex));
	}
	i--;
	if (ex->b_tkn == 4)
		if (!(isalnum(ex->ex_un[i])) && ex->ex_un[i] != '_')
			return (err_msg_env(ex));
	if (ex->b_tkn == 3)
		if (!(isalnum(ex->ex_un[i])) && ex->ex_un[i] != '_' \
			&& ex->ex_un[i] != '+')
			return (err_msg_env(ex));
	return (0);
}

int	chk_and_appoint_env(char *str, t_exe *ex)
{
	int	i;

	i = -1;
	while (str[++i] && ex->b_tkn == 4)
	{
		if (!isalnum(ex->ex_un[i]) && ex->ex_un[i] != '_')
		{
			err_msg_env(ex);
			ft_cautious_free((void **)&ex->ex_un);
			if (ex->cnt_lst)
				ft_cautious_free((void **)&ex->cnt_lst);
			return (1);
		}
	}
	if (chk_valid_env(ex))
	{
		ft_cautious_free((void **)&ex->ex_un);
		if (ex->cnt_lst)
			ft_cautious_free((void **)&ex->cnt_lst);
		return (1);
	}
	return (0);
}

int	exec_env(t_tbl *tbl, t_exe *ex)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	while (tbl->commands[ex->i].arguments && \
		tbl->commands[ex->i].arguments[++i])
	{
		if (name_snatcher(tbl->commands[ex->i].arguments[i], ex))
			continue ;
		ret = chk_and_appoint_env(tbl->commands[ex->i].arguments[i], ex);
		if (ret)
			continue ;
		if (ex->b_tkn == 4 && ft_strncmp("_", ex->ex_un, 2))
			unset_env(tbl, ex);
		if (ex->b_tkn == 3 && ft_strncmp("_", ex->ex_un, 2))
			if ((envport(tbl, ex)) < 0)
				return (-1);
		ft_cautious_free((void **)&ex->ex_un);
		if (ex->cnt_lst)
			ft_cautious_free((void **)&ex->cnt_lst);
	}
	return (ret);
}

int	env(t_tbl *tbl, t_exe *ex)
{
	int	r;

	r = 126;
	if (ex->b_tkn == 5 && tbl->env_lst)
	{
		if (*tbl->commands[ex->i].arguments)
			return (r + ret_putstr_fd("env: %s: No such file or directory\n", \
			ft_strdup(tbl->commands[ex->i].arguments[0]), 2));
		print_em_envs(tbl->env_lst);
		return (0);
	}
	else if (ex->b_tkn == 3 && tbl->env_lst)
	{
		if (!*tbl->commands[ex->i].arguments)
			return (export(tbl->env_lst));
	}
	return (exec_env(tbl, ex));
}
