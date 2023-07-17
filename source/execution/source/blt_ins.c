/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_ins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:16:51 by aikram            #+#    #+#             */
/*   Updated: 2023/03/19 02:57:02 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	pwd(t_tbl *tbl, t_exe *ex)
{
	char	buf[PATH_MAX];

	if (*tbl->commands[ex->i].arguments)
		return (msg_err(ERR_PWD, 1));
	if (getcwd(buf, sizeof(buf)))
		printf("%s\n", buf);
	else
		return (ret_perr("pwd error!"));
	return (0);
}

int	ch_dir(t_tbl *tbl, t_exe *ex)
{
	char	*path;
	int		ret;

	ret = 0;
	if (!*tbl->commands[ex->i].arguments)
		return (cd_home(tbl));
	path = ft_strdup(tbl->commands[ex->i].arguments[0]);
	if (!path)
		return (-1);
	if (cd_util(path))
		return (1);
	ret = cd_pth(tbl, path);
	free(path);
	return (ret);
}

int	echo(t_tbl *tbl, t_exe *ex)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (tbl->commands[ex->i].arguments[++i])
	{
		if (!i && !(ft_strncmp(tbl->commands[ex->i].arguments[i], "-n", 2)))
		{
			j = echo_utils(tbl->commands[ex->i].arguments[i]);
			if (!j && tbl->commands[ex->i].arguments[i + 1])
				printf(" ");
		}
		else
		{
			printf("%s", tbl->commands[ex->i].arguments[i]);
			if (tbl->commands[ex->i].arguments[i + 1] && \
				*tbl->commands[ex->i].arguments[i + 1])
				printf(" ");
		}
	}
	if (!j)
		printf("\n");
	return (0);
}

int	ft_exit(t_tbl *tbl, t_exe *ex)
{
	char	*err;
	int		non_numeric;

	err = NULL;
	non_numeric = 0;
	tbl->exit = true;
	if (tbl->commands[ex->i].arguments != NULL)
		non_numeric = chk_exit_arg(tbl, ex);
	if (non_numeric)
	{
		err = ft_strjoin("minishell: exit", ERR_NAR);
		msg_err(err, 1);
		free(err);
		return (255);
	}
	if (tbl->commands[ex->i].arguments != NULL)
		if (exit_util(tbl, ex, err))
			return (1);
	if (tbl->commands[ex->i].arguments[0])
		return ((unsigned char)(ft_atoi(tbl->commands[ex->i].arguments[0])));
	return (0);
}

int	built_ins(t_tbl *tbl, t_exe *ex)
{
	int	r;

	r = 0;
	piper(ex);
	close_other_pps(ex);
	if (!ex->b_tkn)
		r = echo(tbl, ex);
	else if (ex->b_tkn == 1)
		r = ch_dir(tbl, ex);
	else if (ex->b_tkn == 2)
		r = pwd(tbl, ex);
	else if (ex->b_tkn >= 3 && ex->b_tkn <= 5)
		r = env(tbl, ex);
	else
		r = ft_exit(tbl, ex);
	if (ex->child_support)
	{
		free_pps(ex);
		exit (r);
	}
	return (r);
}
