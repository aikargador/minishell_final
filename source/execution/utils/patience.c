/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patience.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:14:22 by aikram            #+#    #+#             */
/*   Updated: 2023/03/18 19:43:26 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	wait_utils(t_exe *ex, t_tbl *tbl)
{
	if (!WIFEXITED(ex->cause_of_death) && WIFSIGNALED(ex->cause_of_death))
	{
		if (WTERMSIG(ex->cause_of_death) == SIGINT || \
			WTERMSIG(ex->cause_of_death) == SIGQUIT)
			tbl->exit_status = 130;
		if (WTERMSIG(ex->cause_of_death) == SIGQUIT)
		{
			printf("Quit\n");
			tbl->exit_status++;
		}
		return ;
	}
	tbl->exit_status = WEXITSTATUS(ex->cause_of_death);
}

void	patience(t_exe *ex, t_tbl *tbl)
{
	int	i;

	i = -1;
	while (++i < ex->i)
		waitpid(ex->pps->birth_certificate[i], &ex->cause_of_death, 0);
	wait_utils(ex, tbl);
}
