/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:20:57 by aikram            #+#    #+#             */
/*   Updated: 2023/03/18 23:10:09 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

char	**infinity_gauntle(char **ptr, int l)
{
	int	i;

	i = -1;
	while (++i < l)
		ft_cautious_free((void **)&ptr[i]);
	ft_very_cautious_free((void ***)&ptr);
	return (NULL);
}

char	**envstr(t_env *env_lst)
{
	char	**envp;
	char	*tmp;
	int		i[2];

	i[0] = -1;
	tmp = NULL;
	i[1] = ft_listen(&env_lst);
	envp = ft_calloc(i[1] + 1, sizeof(char *));
	if (!envp)
		return (infinity_gauntle(envp, 0));
	while (++i[0] < i[1])
	{
		envp[i[0]] = env_val_join(&env_lst->name, "=", 0, 3);
		if (!envp[i[0]])
			return (infinity_gauntle(envp, i[0]));
		ft_cautious_free((void **)&tmp);
		envp[i[0]] = env_val_join(&envp[i[0]], env_lst->vals, 0, 1);
		if (!envp[i[0]])
			return (infinity_gauntle(envp, i[0]));
		env_lst = env_lst->nxt;
	}
	envp[i[0]] = NULL;
	return (envp);
}

void	other_cmds(t_tbl *tbl, t_exe *ex)
{
	char	*tmp;
	char	**envp;

	envp = envstr(*tbl->env_lst);
	ex->pps->pth_tkn = get_path(ex->pps, tbl->env_lst);
	ex->pps->cmd_arg = split_cmd(&tbl->commands[ex->i]);
	if (!get_cmd(tbl->commands[ex->i].name, ex->pps))
	{
		tmp = ft_strjoin(tbl->commands[ex->i].name, ERR_CMD);
		ret_putstr_fd("cultured shell: %s", tmp, 2);
		ft_free_string_array(&envp);
		close_pps(ex);
		free_child(tbl, ex);
		exit (127);
	}
	chk_inf_ouf(tbl, ex);
	piper(ex);
	close_other_pps(ex);
	execve(ex->pps->cmd_pth, ex->pps->cmd_arg, envp);
	ret_perr(ex->pps->cmd_pth);
	ft_free_string_array(&envp);
	free_child(tbl, ex);
	exit(EXIT_FAILURE);
}
