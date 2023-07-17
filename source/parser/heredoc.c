/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:16:20 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/18 22:04:11 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>

extern t_command_table	g_command_table;	

bool	handle_heredoc_redirection(t_command *command);

bool	handle_heredoc_redirections(t_command *commands)
{
	size_t	commands_index;
	bool	status;

	if (!commands)
		return (false);
	status = true;
	commands_index = 0;
	while (commands[commands_index].name)
	{
		if (commands[commands_index].redirect_info.heredoc_delimiter)
			status = handle_heredoc_redirection(&(commands[commands_index]));
		if (!status)
			return (status);
		commands_index++;
	}
	return (status);
}

int	open_heredoc_for_execution(t_command *command)
{
	command->redirect_info.hrdc_fd = open(HEREDOC_FILENAME, O_RDONLY);
	if (command->redirect_info.hrdc_fd == -1)
	{
		ft_putstr_fd("cultured_shell: heredoc open error!", 2);
		unlink(HEREDOC_FILENAME);
		return (1);
	}
	return (0);
}

char	*get_next_line_wrapper(void)
{
	char	*line;

	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	if (line[0])
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

void	child_heredoc_handler(pid_t pid, t_command *command)
{
	char	*line;
	int		fd;

	g_command_table.child_pid = pid;
	fd = open(HEREDOC_FILENAME, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		handle_error(NULL, 0);
		exit(1);
	}
	line = get_next_line_wrapper();
	while (line && ft_strncmp(line,
			command->redirect_info.heredoc_delimiter, SIZE_MAX) != 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		ft_cautious_free((void **)&line);
		line = get_next_line_wrapper();
	}
	ft_cautious_free((void **)&line);
	close(fd);
	exit(0);
}

bool	handle_heredoc_redirection(t_command *command)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		child_heredoc_handler(pid, command);
	}
	else
	{
		status = waitpid(pid, NULL, 0);
		g_command_table.child_pid = 0;
		if (status == -1)
			return (false);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			ft_putstr_fd("cultured_shell: heredoc open error!", STDERR_FILENO);
			return (false);
		}
		if (open_heredoc_for_execution(command))
			return (false);
	}
	return (true);
}
