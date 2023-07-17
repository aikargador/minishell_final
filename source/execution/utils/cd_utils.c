/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:51:58 by aikram            #+#    #+#             */
/*   Updated: 2023/03/18 19:18:44 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	find_and_update(t_env **env, char *env_var, char *change)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!(ft_strncmp(tmp->name, env_var, env_len(env_var))))
		{
			if (tmp->vals)
				free(tmp->vals);
			tmp->vals = ft_strdup(change);
			if (!tmp->vals)
				return (-1);
			return (0);
		}
		tmp = tmp->nxt;
	}
	return (0);
}

int	update_env(char *env_var, t_tbl *tbl, char *change)
{
	if ((find_and_update(tbl->env_lst, env_var, change) < 0))
		return (-1);
	return (0);
}

int	cd_util(char *path)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (access(path, F_OK) == -1 && !i)
	{
		tmp = ft_strjoin("Cultured shell: cd: ", path);
		ret_perr(tmp);
		i = 1;
	}
	if (i)
	{
		freeple(tmp, path, NULL, 0);
		return (1);
	}
	return (0);
}

int	cd_home(t_tbl *tbl)
{
	t_env	*var;

	if (!*tbl->env_lst)
		return (msg_err("Cultured shell: cd: HOME not set\n", 1));
	var = *tbl->env_lst;
	while (var)
	{
		if (!(ft_strncmp(var->name, "HOME", env_len("HOME"))))
			break ;
		var = var->nxt;
	}
	if (var)
		return (cd_pth(tbl, var->vals));
	else
		return (msg_err("Cultured shell: cd: HOME not set\n", 1));
	return (0);
}

int	cd_pth(t_tbl *tbl, char *path)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
		return (1);
	if (!chdir(path))
	{
		if ((update_env("OLDPWD", tbl, buf)) < 0)
			return (1);
		free(buf);
		buf = getcwd(NULL, 0);
		if (!buf)
			return (1);
		if ((update_env("PWD", tbl, buf)) < 0)
			return (1);
		free(buf);
	}
	else
	{
		free(buf);
		return (ret_perr(path));
	}
	return (0);
}
