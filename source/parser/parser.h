/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 21:29:53 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/18 19:59:37 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <stdint.h>
# include "../../libft/libft.h"

# define HEREDOC_FILENAME ".hrdc_tmp"
# define EMPTY_TOKEN_INDICATOR -1

# define MASKED_DOLLAR_SIGN -25

typedef struct s_redirect_info
{
	char			*redirect_input_source_filename;
	char			*heredoc_delimiter;
	char			*redirect_output_target_filename;
	int				file_opening_flags_input;
	int				file_opening_flags_output;
	int				hrdc_fd;
}	t_redirect_info;

typedef struct s_command
{
	char			*name;
	char			**arguments;
	t_redirect_info	redirect_info;
}	t_command;

// typedef struct s_environment // commented out by kungus khan
// {
// 	char		**names;
// 	char		**values;
// }	t_environment;

/*  changed made by kungus khan:
	parser.h -> added improved environment map! bruh!
		line 42 -> 65, 71, 109, 110, 112 -> 120, 140, 141
	main.c -> added improved positioning of env!
		26, 28, 29, 41
	environment.c -> added new env collector!, lol nearly everything changed!
		17 -> 79, added kungus khan header -> 82 -> 84, 87 -> 122
	parce.c -> bloack commented out every instance of depricated environment
		line 15, 21, 33, 35, 38

*/

typedef struct s_env { // added by kungus_khan
	char			*name;
	char			*vals;
	struct s_env	*nxt;
}	t_env;

typedef struct s_command_table
{
	t_command		*commands;
	t_env			**env_lst;
	pid_t			child_pid;
	int				exit_status;
	int				dumb;
	bool			exit;
}	t_command_table;

// # include "../execution/includes/execution.h"

void			mask_solitary_quotes(char *line);
void			unmask_solitary_quotes(t_command *commands);

size_t			*mask_whitespaces_to_be_ignored(char *line);
void			unmask_ignored_whitespaces(char **tokens);

size_t			calculate_expanded_line_length(const char *line,
					int last_exit_status);
size_t			get_variable_name_length(const char *line, size_t index);
void			get_variable_name(const char *line, size_t line_index,
					char *variable_identifier_target);

char			*do_expansions(char *line, int last_exit_status);

void			fill_separators(char *separators);
char			*separate_special_tokens(char *line);

char			**line_into_tokens(char *line);
void			free_2d_array(char **tokens);

t_command		*tokens_into_commands(char **tokens);
size_t			count_command_arguments(char **tokens);
size_t			count_commands(char **tokens);
t_command		*allocate_memory_for_commands(char **tokens);

bool			encode_redirections(t_command *commands);
bool			add_redirection(t_redirect_info *redirect_info,
					char *redirection_symbol, char *filename_or_delimiter);

t_env			*get_em_envs(char **e, void *(*f)(void *), void (*del)(void *));
t_env			*get_em_exps(char **e, t_command_table *tbl);
void			sort_env(t_env **exp, int end);
void			print_em_envs(t_env **env);
void			free_commands(t_command **commands);
void			free_env(t_env **env, void (*del)(void *));
// void			free_arg(void *arg);
void			chk_ptr_free(void *ptr);

/* env_utils, utilities/env_utils.c */
t_env			*ft_env_lstlast(t_env *lst);
t_env			*ft_env_lstnew(void *cnt1, void *cnt2);
void			ft_env_lstadd_back(t_env **lst, t_env *new);
void			ft_env_lstclear(t_env **lst, void (*del)(void *));
void			ft_env_lstdelone(t_env *lst, void (*del)(void *));
char			**env_split(char const *s, char c);

char			*remove_literal_interpretation_indicators_from_token(
					char *string, char c, char d);
void			remove_literal_interpretation_indicators_from_commands(
					t_command *commands);

void			mask_heredoc_dollar_signs(char *line);
bool			handle_heredoc_redirections(t_command *commands);
void			unmask_heredoc_dollar_signs(char *line);

t_command		*parse(char *line, int last_exit_status);
void			clean_command_table(void);
void			free_command_table(void);

void			handle_error(char *error_message, int custom_errno);
void			terminate_minishell(int exit_status, char *error_message);

int				main(int argc, char **argv, char **envp);
void			refresh_minishell(char *error_message, char **envp);

// For testing purposes
void			test_print_commands(t_command *commands);

void			ctrl_c_hrdc(int signal_num);

#endif
