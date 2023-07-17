/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_the_door.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:33:36 by aikram            #+#    #+#             */
/*   Updated: 2023/03/19 02:04:03 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	close_fds(t_tbl *tbl, t_exe *ex)
{
	if (tbl->commands[ex->hrdc_ache].redirect_info.heredoc_delimiter)
		cautious_close(tbl->commands[ex->hrdc_ache].redirect_info.hrdc_fd);
	else if (ex->pps->inf_tkn)
		cautious_close(ex->inf);
	if (ex->pps->ouf_tkn)
		cautious_close(ex->ouf);
}

void	cls_pps(t_exe *ex, int i)
{
	if (ex->pps->pp[i][0])
		cautious_close(ex->pps->pp[i][0]);
	if (ex->pps->pp[i][1])
		cautious_close(ex->pps->pp[i][1]);
}

void	close_pps(t_exe *ex)
{
	int	i;

	i = -1;
	if (ex->amt_pipe)
	{
		while (++i < ex->amt_pipe)
			cls_pps(ex, i);
		free_pps(ex);
	}
}

void	blt_chk_cls(t_tbl *tbl, t_exe *ex, int *std)
{
	if (tbl->commands[ex->i].redirect_info.heredoc_delimiter)
	{
		dup2(std[0], STDIN_FILENO);
		cautious_close(std[0]);
	}
	else if (ex->pps->inf_tkn)
	{
		dup2(std[0], STDIN_FILENO);
		cautious_close(std[0]);
	}
	if (ex->pps->ouf_tkn)
	{
		dup2(std[1], STDOUT_FILENO);
		cautious_close(std[1]);
	}
}

void	close_other_pps(t_exe *ex)
{
	int	i;

	i = -1;
	if (!ex->amt_pipe)
		return ;
	if (!ex->i)
		cautious_close(ex->pps->pp[0][0]);
	if (!ex->i)
		i = 0;
	while (++i < ex->amt_pipe)
	{
		if ((ex->i == ex->amt_pipe) && (i == (ex->i - 1)))
		{
			cautious_close(ex->pps->pp[i][1]);
			break ;
		}
		else if (i == (ex->i - 1))
		{
			cautious_close(ex->pps->pp[i][1]);
			i++;
			cautious_close(ex->pps->pp[i][0]);
			continue ;
		}
		cls_pps(ex, i);
	}
}
