/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:41:47 by aikram            #+#    #+#             */
/*   Updated: 2023/03/19 08:33:33 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	env_swap(t_env **ptr_a, t_env **ptr_b)
{
	char	*name;
	char	*vals;

	if (ft_strcmp((*ptr_a)->name, (*ptr_b)->name) > 0)
	{
		name = (*ptr_a)->name;
		vals = (*ptr_a)->vals;
		(*ptr_a)->name = (*ptr_b)->name;
		(*ptr_a)->vals = (*ptr_b)->vals;
		(*ptr_b)->name = name;
		(*ptr_b)->vals = vals;
	}
}

void	sort_env(t_env **exp, int end)
{
	int		i[2];
	t_env	*ptr_a;
	t_env	*ptr_b;

	i[0] = 0;
	ptr_a = *exp;
	while (i[0] < end - 1)
	{
		i[1] = i[0];
		ptr_b = ptr_a->nxt;
		while (++i[1] < end)
		{
			env_swap(&ptr_a, &ptr_b);
			ptr_b = ptr_b->nxt;
		}
		ptr_a = ptr_a->nxt;
		i[0]++;
	}
}

int	envport(t_tbl *tbl, t_exe *ex)
{
	t_env	*lst;
	char	*ex_un;

	if (!*tbl->env_lst)
		lst = NULL;
	else
		lst = *tbl->env_lst;
	ex_un = NULL;
	ex_un = chk_plus(ex);
	if (!ex_un)
		return (-1);
	if (ft_strncmp(ex_un, "TERM", 5) && ex->cnt_lst)
		tbl->dumb = 0;
	while (lst)
	{
		if (!ft_strncmp(lst->name, ex_un, env_len(ex_un)))
			break ;
		lst = lst->nxt;
	}
	if (lst)
		ft_cautious_free((void **)&ex_un);
	if (lst)
		return (chk_append(&lst, ex));
	add_env(tbl, ex, ex_un);
	return (0);
}

int	export_utils(t_env **ptr, t_env *tmp)
{
	char	*val;

	if (tmp->vals)
	{
		val = env_val_join(&tmp->vals, ft_strdup("=\""), 1, 0);
		if (!val)
			return (1);
		val = env_val_join(&val, ft_strdup("\""), 0, 2);
		if (!val)
			return (1);
	}
	if (&*tmp->vals && !*tmp->vals)
	{
		val = ft_strdup("=\"\"");
		if (!val)
			return (1);
	}
	else if (!&*tmp->vals)
		val = NULL;
	ft_env_lstadd_back(ptr, ft_env_lstnew(ft_strdup(tmp->name), \
		ft_strdup(val)));
	ft_cautious_free((void **)&val);
	return (0);
}

int	export(t_env **env)
{
	t_env	**ptr;
	t_env	*tmp;
	int		i;

	tmp = *env;
	i = ft_listen(env);
	ptr = ft_calloc(1, sizeof(t_env *));
	if (!ptr)
		return (1);
	while (tmp)
	{
		if (export_utils(ptr, tmp))
			return (1);
		tmp = tmp->nxt;
	}
	sort_env(ptr, i);
	print_em_exps(ptr);
	ft_env_lstclear(ptr, free);
	return (0);
}
