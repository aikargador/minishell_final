/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plumber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 10:31:37 by aikram            #+#    #+#             */
/*   Updated: 2023/03/19 02:35:56 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	free_inner_pp(t_exe *ex, int l, char *blame)
{
	int	i;

	i = -1;
	while (++i < l)
	{
		cautious_close(ex->pps->pp[i][0]);
		cautious_close(ex->pps->pp[i][1]);
		ft_cautious_free((void **)&ex->pps->pp[i]);
	}
	ft_very_cautious_free((void ***)&ex->pps->pp);
	return (ret_perr(blame));
}

int	creat_pps(t_pps *pps, t_exe *ex)
{
	int	i;

	i = -1;
	pps->pp = NULL;
	if (ex->amt_pipe)
	{
		pps->pp = (int **)ft_calloc(ex->amt_pipe, sizeof(int *));
		if (!pps->pp)
			return (ret_perr(ERR_MPP));
	}
	while (++i < ex->amt_pipe)
	{
		pps->pp[i] = (int *)ft_calloc(2, sizeof(int));
		if (!pps->pp[i])
			return (free_inner_pp(ex, i, ERR_MPP));
		if (pipe(pps->pp[i]) == -1)
			return (free_inner_pp(ex, i, ERR_PPE));
	}
	return (0);
}

void	piper(t_exe *ex)
{
	if (!ex->amt_pipe)
		return ;
	if (!ex->i)
	{
		if (!ex->pps->ouf_tkn)
			dup2(ex->pps->pp[0][1], STDOUT_FILENO);
		cautious_close(ex->pps->pp[0][1]);
	}
	else if (ex->i == ex->amt_pipe)
	{
		if (!ex->pps->inf_tkn)
			dup2(ex->pps->pp[ex->i - 1][0], STDIN_FILENO);
		cautious_close(ex->pps->pp[ex->i - 1][0]);
	}
	else
	{
		if (!ex->pps->inf_tkn)
			dup2(ex->pps->pp[ex->i - 1][0], STDIN_FILENO);
		cautious_close(ex->pps->pp[ex->i - 1][0]);
		if (!ex->pps->ouf_tkn)
			dup2(ex->pps->pp[ex->i][1], STDOUT_FILENO);
		cautious_close(ex->pps->pp[ex->i][1]);
	}
}
