/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_unset_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:00:50 by aikram            #+#    #+#             */
/*   Updated: 2023/03/19 08:22:48 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	chk_sneaky_plus(char *str)
{
	size_t	l;

	l = 0;
	while (str[l] != '\0' && str[l] != '=')
		l++;
	if (!str[l] && l)
	{
		l--;
		if (str[l] == '+')
		{
			str = env_val_join(&str, "minishell: export: ", 1, 3);
			str = env_val_join(&str, ": not a valid identifier\n", 0, 1);
			ft_putstr_fd(str, 2);
			ft_cautious_free((void **)&str);
			return (1);
		}
	}
	return (0);
}

int	environment_free_from_plastic(char **plastic)
{
	ft_cautious_free((void **)&plastic[0]);
	if (plastic[1])
		ft_cautious_free((void **)&plastic[1]);
	ft_very_cautious_free((void ***)&plastic);
	return (1);
}

int	name_snatch_utls(char **env_node, t_exe *ex, char *str)
{
	if (!env_node[1])
		ex->cnt_lst = NULL;
	else
	{
		ex->cnt_lst = ft_strdup(env_node[1]);
		if (!ex->cnt_lst)
		{
			ft_cautious_free((void **)&ex->ex_un);
			return (environment_free_from_plastic(env_node));
		}
	}
	if (chk_sneaky_plus(str))
	{
		ft_cautious_free((void **)&ex->ex_un);
		if (ex->cnt_lst)
			ft_cautious_free((void **)&ex->cnt_lst);
		return (environment_free_from_plastic(env_node));
	}
	freeple(env_node[0], env_node[1], env_node, 1);
	return (0);
}

int	name_snatcher(char *str, t_exe *ex)
{
	char	**env_node;

	env_node = env_split(str, '=');
	if (!env_node[0] || !*env_node[0] || !ft_strncmp(str, "=", 2)
		|| !ft_strncmp(str, "+=", 3))
	{
		ex->ex_un = env_node[0];
		if (!ft_strncmp(str, "=", 2))
			ex->ex_un = "=";
		if (!ft_strncmp(str, "+=", 3))
			ex->ex_un = "+=";
		ex->cnt_lst = env_node[1];
		err_msg_env(ex);
		return (environment_free_from_plastic(env_node));
	}
	ex->ex_un = ft_strdup(env_node[0]);
	if (!ex->ex_un)
		return (environment_free_from_plastic(env_node));
	return (name_snatch_utls(env_node, ex, str));
}

int	err_msg_env(t_exe *ex)
{
	char	*err;
	char	*exp;
	char	*uns;

	err = NULL;
	exp = "Cultured shell: export: %s: not a valid identifier\n";
	uns = "Cultured shell: unset: %s: not a valid identifier\n";
	if (ex->b_tkn == 3)
		return (ret_putstr_fd(exp, ft_strjoin(ex->ex_un, ex->cnt_lst), 2));
	if (ex->cnt_lst && *ex->cnt_lst)
	{
		err = ft_strjoin("=", ex->cnt_lst);
		err = env_val_join(&err, ex->ex_un, 1, 1);
		return (ret_putstr_fd(uns, err, 2));
	}
	return (ret_putstr_fd(uns, ft_strjoin(ex->ex_un, ex->cnt_lst), 2));
}
