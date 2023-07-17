/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:56:18 by aikram            #+#    #+#             */
/*   Updated: 2023/03/31 21:40:38 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

extern t_command_table	g_command_table;

void	child_labor(t_exe *ex)
{
	while (g_command_table.commands[++ex->i].name)
	{
		ex->pps->birth_certificate[ex->i] = fork();
		if (ex->pps->birth_certificate[ex->i] == -1)
		{
			g_command_table.exit_status = ret_perr(ERR_FRK);
			return ;
		}
		if (ex->pps->birth_certificate[ex->i] == 0)
		{
			ex->child_support = 1;
			if (chk_blt(g_command_table.commands[ex->i].name, ex) != -1)
			{
				if (ex->pps->inf_tkn || ex->pps->ouf_tkn)
					chk_inf_ouf(&g_command_table, ex);
				built_ins(&g_command_table, ex);
			}
			else
				other_cmds(&g_command_table, ex);
		}
		g_command_table.child_pid = ex->pps->birth_certificate[ex->i];
	}
	close_pps(ex);
	patience(ex, &g_command_table);
}

void	executor(t_exe *ex)
{
	ex->pps->pth_tkn = 1;
	ex->child_support = 0;
	if (!ex->amt_pipe)
	{
		if (chk_blt(g_command_table.commands[++ex->i].name, ex) != -1)
			blt_chk_iof(&g_command_table, ex);
		else
		{
			ex->i = -1;
			child_labor(ex);
		}
	}
	else
		child_labor(ex);
}

void	file_opener(t_exe *ex)
{
	printf("ex->i %d\n", ex->i);
	printf("ouf name %s\n", g_command_table.commands[ex->i]
				.redirect_info.redirect_output_target_filename);
	ex->cls_hrdc = 0;
	if (g_command_table.commands[ex->i]
		.redirect_info.redirect_input_source_filename)
	{
		ex->pps->inf_tkn = 1;
		ex->inf = open(
				g_command_table.commands[ex->i]
				.redirect_info.redirect_input_source_filename,
				g_command_table.commands[ex->i].redirect_info
				.file_opening_flags_input);
		if (ex->inf == -1)
			g_command_table.exit_status = ret_perr(ERR_INF);
	}
	if (g_command_table.commands[ex->i]
		.redirect_info.redirect_output_target_filename)
	{
		ex->pps->ouf_tkn = 1;
		ex->ouf = open(
				g_command_table.commands[ex->i]
				.redirect_info.redirect_output_target_filename,
				g_command_table.commands[ex->i].redirect_info
				.file_opening_flags_output, 0644);
		if (ex->ouf == -1)
			g_command_table.exit_status = ret_perr(ERR_OUF);
	}
}

void	tuberculosis_printf()
{
	int	i = -1;
	while (g_command_table.commands[++i].name != NULL)
	{
		printf("Command Name: %s\n", g_command_table.commands[i].name);
		printf("Command Arguments: ");
		for (int arguments_index = 0; g_command_table.commands[i].arguments[arguments_index] != NULL; arguments_index++)
		{
			if (g_command_table.commands[i].arguments[arguments_index + 1] != NULL)
				printf("%s, ", g_command_table.commands[i].arguments[arguments_index]);
			else
				printf("%s", g_command_table.commands[i].arguments[arguments_index]);
		}
		printf("\n");
		printf("child pid %d\n", g_command_table.child_pid);
		printf("exit or nope: %d\n", g_command_table.exit);
		printf("exit stat %d\n", g_command_table.exit_status);
		printf("Redirect Input Source Filename: %s\n", g_command_table.commands[i].redirect_info.redirect_input_source_filename);
		printf("Heredoc Delimiter: %s\n", g_command_table.commands[i].redirect_info.heredoc_delimiter);
		printf("Redirect Output Target Filename: %s\n", g_command_table.commands[i].redirect_info.redirect_output_target_filename);
		printf("File Opening Flags Input: %d\n", g_command_table.commands[i].redirect_info.file_opening_flags_input);
		printf("File Opening Flags Output: %d\n", g_command_table.commands[i].redirect_info.file_opening_flags_output);
	}
}

void	execute(void)
{
	t_exe	ex;
	t_pps	pps;

	ex.pps = &pps;
	g_command_table.exit = false;
	g_command_table.exit_status = 0;
	ex.cls_hrdc = 0;
	ex.hrdc_ache = 0;
	ex.pps->inf_tkn = 0;
	ex.pps->ouf_tkn = 0;
	ex.i = -1;
	// tuberculosis_printf();
	while (&g_command_table.commands[++ex.i] && \
		g_command_table.commands[ex.i].name)
		;
	ex.pps->birth_certificate = ft_calloc(ex.i, sizeof(pid_t));
	ex.amt_pipe = ex.i - 1;
	if (ex.amt_pipe)
		creat_pps(ex.pps, &ex);
	ex.i = -1;
	if (g_command_table.exit_status)
		return ;
	executor(&ex);
	parent_free_from_trouble(&g_command_table, &ex);
}
