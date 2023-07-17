/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:23:50 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/19 02:07:08 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"

t_command_table	g_command_table;

void	main_loop(char *line)
{
	while (true)
	{
		line = readline("\001\033[1;38;5;29m\002Cultured_shell$ \001\033[0m\002");
		if (line == NULL)
			break ;
		if (!is_empty_line(line))
		{
			add_history(line);
			if (has_syntax_error(line))
			{
				ft_cautious_free((void **)&line);
				ft_putstr_fd("cultured shell: syntax error.\n", STDERR_FILENO);
				continue ;
			}
			g_command_table.commands = parse(line, g_command_table.exit_status);
			clean_command_table();
			if (g_command_table.commands)
				execute();
			free_commands(&(g_command_table.commands));
			g_command_table.commands = NULL;
			if (g_command_table.exit)
				break ;
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;

	(void)argc;
	(void)argv;
	line = NULL;
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_backslash_handler);
	g_command_table.dumb = 0;
	g_command_table.env_lst = ft_calloc(1, sizeof(t_env *));
	if (!g_command_table.env_lst)
		return (-1);
	*g_command_table.env_lst = get_em_envs(envp, (void *)ft_strdup, free_str);
	main_loop(line);
	ft_env_lstclear(g_command_table.env_lst, free);
	(void)envp;
	return (g_command_table.exit_status);
}
