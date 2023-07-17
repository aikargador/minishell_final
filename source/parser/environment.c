/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:42:48 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/18 21:28:15 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

extern t_command_table	g_command_table;

void	emp_env_init(t_env **env)
{
	char	*buf;

	g_command_table.dumb = 1;
	*env = ft_env_lstnew(ft_strdup("OLDPWD"), NULL);
	if (!*env)
		return ;
	buf = getcwd(NULL, 0);
	if (!buf)
		return ;
	ft_env_lstadd_back(env, ft_env_lstnew(ft_strdup("PWD"), buf));
}

t_env	*get_em_envs(char **e, void *(*f)(void *), void (*del)(void *))
{
	char	**arr;
	t_env	*ptr;
	t_env	*tmp;

	ptr = NULL;
	if (!*e)
		emp_env_init(&ptr);
	while (*e)
	{
		arr = env_split(*e, '=');
		if (!arr)
			return (NULL);
		tmp = ft_env_lstnew(f(arr[0]), f(arr[1]));
		if (!tmp->name || !tmp->vals)
		{
			ft_env_lstclear(&ptr, del);
			return (NULL);
		}
		ft_env_lstadd_back(&ptr, tmp);
		ft_cautious_free((void **)&arr[0]);
		ft_cautious_free((void **)&arr[1]);
		ft_very_cautious_free((void ***)&arr);
		e++;
	}
	return (ptr);
}
