/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 23:22:55 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/18 22:43:05 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../parser.h"

bool	check_null_pointers(t_redirect_info *redirect_info,
			char *redirection_symbol, char *filename_or_delimiter);
bool	add_input_redirection(t_redirect_info *redirect_info,
			char *filename_or_delimiter);
bool	add_output_redirection(t_redirect_info *redirect_info,
			char *filename_or_delimiter);
bool	add_output_redirection_append(t_redirect_info *redirect_info,
			char *filename_or_delimiter);
bool	add_heredoc_redirection(t_redirect_info *redirect_info,
			char *delimiter);

bool	add_redirection(t_redirect_info *redirect_info,
			char *redirection_symbol, char *filename_or_delimiter)
{
	bool	status;

	if (!check_null_pointers(redirect_info, redirection_symbol,
			filename_or_delimiter))
		return (false);
	status = true;
	if (ft_strncmp(redirection_symbol, ">", 2) == 0)
		status = add_output_redirection(redirect_info, filename_or_delimiter);
	else if (ft_strncmp(redirection_symbol, "<", 2) == 0)
		status = add_input_redirection(redirect_info, filename_or_delimiter);
	else if (ft_strncmp(redirection_symbol, ">>", 3) == 0)
		status = add_output_redirection_append(
				redirect_info, filename_or_delimiter);
	else if (ft_strncmp(redirection_symbol, "<<", 3) == 0)
		add_heredoc_redirection(redirect_info, filename_or_delimiter);
	return (status);
}

bool	add_input_redirection(t_redirect_info *redirect_info,
			char *filename_or_delimiter)
{
	int		fd;

	if (redirect_info->redirect_input_source_filename)
	{
		fd = open(redirect_info->redirect_input_source_filename,
				O_RDONLY, 0644);
		if (fd == -1)
		{
			handle_error(NULL, 0);
			return (false);
		}
		close(fd);
		ft_cautious_free((void **)&(
				redirect_info->redirect_input_source_filename));
	}
	fd = open(filename_or_delimiter, O_RDONLY, 0644);
	if (fd == -1)
	{
		handle_error(NULL, 0);
		return (false);
	}
	close(fd);
	redirect_info->redirect_input_source_filename = filename_or_delimiter;
	redirect_info->file_opening_flags_input = O_RDONLY;
	return (true);
}

bool	add_output_redirection(t_redirect_info *redirect_info,
			char *filename_or_delimiter)
{
	int		fd;

	if (redirect_info->redirect_output_target_filename)
	{
		fd = open(redirect_info->redirect_output_target_filename,
				O_TRUNC | O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
		{
			handle_error(NULL, 0);
			return (false);
		}
		close(fd);
		ft_cautious_free((void **)&(
				redirect_info->redirect_output_target_filename));
	}
	redirect_info->redirect_output_target_filename = filename_or_delimiter;
	redirect_info->file_opening_flags_output
		= O_TRUNC | O_WRONLY | O_CREAT;
	return (true);
}

bool	add_output_redirection_append(t_redirect_info *redirect_info,
			char *filename_or_delimiter)
{
	int		fd;

	if (redirect_info->redirect_output_target_filename)
	{
		fd = open(redirect_info->redirect_output_target_filename,
				O_APPEND | O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
		{
			handle_error(NULL, 0);
			return (false);
		}
		close(fd);
		ft_cautious_free((void **)&(
				redirect_info->redirect_output_target_filename));
	}
	redirect_info->redirect_output_target_filename = filename_or_delimiter;
	redirect_info->file_opening_flags_output
		= O_APPEND | O_WRONLY | O_CREAT;
	return (true);
}

bool	add_heredoc_redirection(t_redirect_info *redirect_info, char *delimiter)
{
	if (!redirect_info || !delimiter)
	{
		handle_error("add_redirection_heredoc: null pointer", 1);
		return (false);
	}
	if (redirect_info->heredoc_delimiter)
	{
		ft_cautious_free((void **)
			&(redirect_info->heredoc_delimiter));
		redirect_info->heredoc_delimiter = NULL;
	}
	redirect_info->heredoc_delimiter = delimiter;
	return (true);
}
