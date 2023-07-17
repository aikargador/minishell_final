/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utilities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:59:27 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/19 10:22:40 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"

t_env	*ft_env_lstlast(t_env *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->nxt != NULL)
		lst = lst->nxt;
	return (lst);
}

void	ft_env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*node;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	node = ft_env_lstlast(*lst);
	node->nxt = new;
}

void	ft_env_lstdelone(t_env *lst, void (*del)(void *))
{
	if (lst && del)
	{
		if (lst->name)
			del(lst->name);
		if (lst->vals)
			del(lst->vals);
		if (lst)
			free(lst);
	}
}

void	ft_env_lstclear(t_env **lst, void (*del)(void *))
{
	t_env	*tmp;

	if (*lst == NULL || del == NULL)
		return ;
	while ((*lst) != NULL)
	{
		tmp = (*lst);
		(*lst) = (*lst)->nxt;
		ft_env_lstdelone(tmp, del);
	}
	ft_very_cautious_free((void ***)&lst);
}

t_env	*ft_env_lstnew(void *cnt1, void *cnt2)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (new == NULL)
		return (NULL);
	if (cnt1)
		new->name = cnt1;
	else
		new->name = NULL;
	if (cnt2)
		new->vals = cnt2;
	else
		new->vals = NULL;
	new->nxt = NULL;
	return (new);
}
