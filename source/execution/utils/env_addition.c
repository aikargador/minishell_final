/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_addition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 21:05:28 by aikram            #+#    #+#             */
/*   Updated: 2023/03/19 10:20:02 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	add_env(t_tbl *tbl, t_exe *ex, char *ex_un)
{
	ft_env_lstadd_back(tbl->env_lst, ft_env_lstnew(ft_strdup(ex_un),
			ft_strdup(ex->cnt_lst)));
	ft_cautious_free((void **)&ex_un);
}
