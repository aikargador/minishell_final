/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 10:11:18 by aikram            #+#    #+#             */
/*   Updated: 2023/03/19 08:36:36 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	print_em_exps(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (&*tmp->vals)
			printf("declare -x %s%s\n", tmp->name, tmp->vals);
		else
			printf("declare -x %s\n", tmp->name);
		tmp = tmp->nxt;
	}
}

int	ft_listen(t_env	**env)
{
	int		i;
	t_env	*ptr;

	i = 0;
	ptr = *env;
	while (ptr && ++i)
		ptr = ptr->nxt;
	return (i);
}

char	*chk_plus(t_exe *ex)
{
	char	*trim;
	int		p;

	p = 0;
	ex->plus = 0;
	trim = NULL;
	p = ft_strlen(ex->ex_un);
	if (p)
		p--;
	if (ex->ex_un[p] == '+')
	{
		trim = ft_strtrim(ex->ex_un, "+");
		if (!trim)
			return (NULL);
		ex->plus = 1;
	}
	else
	{
		trim = ft_strdup(ex->ex_un);
		if (!trim)
			return (NULL);
	}
	return (trim);
}

int	chk_app_utils(t_env **env, t_exe *ex)
{
	if ((*env)->vals)
		(*env)->vals = env_val_join(&(*env)->vals, ex->cnt_lst, 0, 3);
	else if (ex->cnt_lst)
		(*env)->vals = ft_strdup(ex->cnt_lst);
	else
		(*env)->vals = ft_calloc(1, sizeof(char *));
	if (!(*env)->vals)
		return (-1);
	return (0);
}

int	chk_append(t_env **env, t_exe *ex)
{
	if (!ex->cnt_lst)
		return (0);
	if (ex->plus)
		return (chk_app_utils(env, ex));
	if ((*env)->vals)
		free((*env)->vals);
	(*env)->vals = ft_strdup(ex->cnt_lst);
	if (!(*env)->vals)
		return (-1);
	return (0);
}
