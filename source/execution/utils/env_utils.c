/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:10:06 by aikram            #+#    #+#             */
/*   Updated: 2023/03/19 10:24:31 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

size_t	env_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i + 1);
}

void	print_em_envs(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (&*tmp->vals)
			printf("%s=%s\n", tmp->name, tmp->vals);
		tmp = tmp->nxt;
	}
}

void	check_unset(t_env *node, t_env *nxt_node)
{
	if (node->nxt && (nxt_node->nxt != NULL))
	{
		node->nxt = nxt_node->nxt;
		ft_env_lstdelone(nxt_node, (void *)free_str);
		return ;
	}
	ft_env_lstdelone(node->nxt, (void *)free_str);
	node->nxt = NULL;
	return ;
}

void	chk_term(t_tbl *tbl, t_exe *ex)
{
	if (!ft_strncmp(ex->ex_un, "TERM", 5))
		tbl->dumb = 0;
}

void	unset_env(t_tbl *tbl, t_exe *ex)
{
	t_env	*lst;
	t_env	*tmp;

	if (!*tbl->env_lst)
		return ;
	lst = *tbl->env_lst;
	if (!ft_strncmp(lst->name, ex->ex_un, env_len(ex->ex_un)))
	{
		chk_term(tbl, ex);
		ft_env_lstdelone(*tbl->env_lst, (void *)free_str);
		*tbl->env_lst = (*tbl->env_lst)->nxt;
		return ;
	}
	while (lst->nxt)
	{
		tmp = lst->nxt;
		if (!ft_strncmp(tmp->name, ex->ex_un, env_len(ex->ex_un)))
			break ;
		lst = lst->nxt;
	}
	if (!lst->nxt)
		return ;
	chk_term(tbl, ex);
	check_unset(lst, tmp);
}
