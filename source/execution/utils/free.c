/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:12:41 by aikram            #+#    #+#             */
/*   Updated: 2023/03/19 00:22:23 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	free_pps(t_exe *ex)
{
	int	i;

	i = -1;
	if (!ex->amt_pipe)
		return ;
	while (++i < ex->amt_pipe)
		ft_cautious_free((void **)&ex->pps->pp[i]);
	ft_very_cautious_free((void ***)&ex->pps->pp);
}

void	parent_free_from_trouble(t_tbl *tbl, t_exe *ex)
{
	ft_cautious_free((void **)&ex->pps->birth_certificate);
	close_fds(tbl, ex);
	if (tbl->commands[ex->hrdc_ache].redirect_info.heredoc_delimiter)
		unlink(".hrdc_tmp");
}

void	free_child(t_tbl *tbl, t_exe *ex)
{
	int	i;

	i = -1;
	parent_free_from_trouble(tbl, ex);
	if (!ex->pps->pth_tkn)
	{
		i = -1;
		while (ex->pps->pths[++i])
			if (ex->pps->pths[i])
				free(ex->pps->pths[i]);
		free(ex->pps->pths);
	}
	i = -1;
	while (ex->pps->cmd_arg[++i])
		free(ex->pps->cmd_arg[i]);
	free(ex->pps->cmd_arg);
	if (ex->pps->cmd_pth)
		free (ex->pps->cmd_pth);
	free_command_table();
}

void	free_str(void *arg)
{
	if (arg)
		free (arg);
}

void	freeple(char *a, char *b, char **c, int i)
{
	ft_cautious_free((void **)&a);
	ft_cautious_free((void **)&b);
	if (i)
		ft_very_cautious_free((void ***)&c);
}
