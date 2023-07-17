/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traffic_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 10:39:35 by aikram            #+#    #+#             */
/*   Updated: 2023/03/19 15:21:07 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	cautious_close(int fd)
{
	int	chk;

	chk = close(fd);
	if (chk == -1)
		return (ret_perr("close"));
	return (0);
}

void	chk_inf_ouf(t_tbl *tbl, t_exe *ex)
{
	file_opener(ex);
	if (tbl->commands[ex->i].redirect_info.heredoc_delimiter)
	{
		ex->cls_hrdc = 1;
		ex->hrdc_ache = ex->i;
		dup2(tbl->commands[ex->i].redirect_info.hrdc_fd, STDIN_FILENO);
		cautious_close(tbl->commands[ex->i].redirect_info.hrdc_fd);
	}
	else if (ex->pps->inf_tkn)
	{
		dup2(ex->inf, STDIN_FILENO);
		cautious_close(ex->inf);
	}
	if (ex->pps->ouf_tkn)
	{
		dup2(ex->ouf, STDOUT_FILENO);
		cautious_close(ex->ouf);
	}
	return ;
}

void	inf_chk(int *std, t_tbl *tbl, t_exe *ex)
{
	printf("hrdc tkn %d\n", tbl->commands[0].redirect_info.hrdc_fd);
	printf("inf tkn %d\n", ex->pps->inf_tkn);
	if (tbl->commands[0].redirect_info.heredoc_delimiter)
	{
		ex->cls_hrdc = 1;
		ex->hrdc_ache = ex->hrdc_ache;
		std[0] = dup(STDIN_FILENO);
		dup2(tbl->commands[0].redirect_info.hrdc_fd, STDIN_FILENO);
		cautious_close(tbl->commands[0].redirect_info.hrdc_fd);
	}
	else if (ex->pps->inf_tkn)
	{
		std[0] = dup(STDIN_FILENO);
		dup2(ex->inf, STDIN_FILENO);
		cautious_close(ex->inf);
	}
}

void	blt_chk_iof(t_tbl *tbl, t_exe *ex)
{
	int	std[2];

	std[0] = 0;
	std[1] = 1;
	file_opener(ex);
	inf_chk(std, tbl, ex);
	printf("ouf tkn %d\n", ex->pps->ouf_tkn);
	if (ex->pps->ouf_tkn)
	{
		std[1] = dup(STDOUT_FILENO);
		printf("hello\n");
		dup2(ex->ouf, STDOUT_FILENO);
		// printf("wello\n");
		cautious_close(ex->ouf);
	}
	tbl->exit_status = built_ins(tbl, ex);
	blt_chk_cls(tbl, ex, std);
	return ;
}
