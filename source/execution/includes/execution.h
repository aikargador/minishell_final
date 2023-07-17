/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:32:57 by aikram            #+#    #+#             */
/*   Updated: 2023/03/19 10:20:07 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>

# include "../../minishell.h"

# define ERR_PPE "error_pipe\n"
# define ERR_MPP "error_malc\n"
# define ERR_FRK "error_fork\n"
# define ERR_PTH "error_path\n"
# define ERR_INF "error_infile\n"
# define ERR_OUF "error_outfile\n"
# define ERR_INP "error_argc.\n"
# define ERR_HDF "error_heredoc\n"
# define ERR_CMD ": command not found\n"
# define ERR_PWD "pwd: too many arguments\n"
# define ERR_TAG ": too many arguments\n"
# define INC_ARG ": incorrect argument count\n"
# define ERR_FDR ": No such file or directory\n"
# define ERR_NAR ": numeric argument required!\n"

typedef t_redirect_info	t_inf_re;

typedef t_command		t_cmd;

typedef t_command_table	t_tbl;

typedef struct s_pps {
	int		pth_tkn;
	int		inf_tkn;
	int		ouf_tkn;
	char	**pths;
	char	*cmd_pth;
	char	**cmd_arg;
	pid_t	*birth_certificate;

	int		**pp;
}	t_pps;

typedef struct s_exe {
	t_pps	*pps;
	int		i;
	int		b_tkn;
	int		p_tkn;
	int		cls_hrdc;
	int		hrdc_ache;
	char	*ex_un;
	char	*cnt_lst;
	int		plus;
	int		bad_no;
	int		child_support;

	int		inf;
	int		ouf;
	int		amt_pipe;
	pid_t	pid;
	int		cause_of_death;
	int		ext_stat;
}	t_exe;

/* blt_ins */
void	free_pps(t_exe *ex);
int		pwd(t_tbl *cnt, t_exe *ex);
int		echo(t_tbl *cnt, t_exe *ex);
int		ft_exit(t_tbl *cnt, t_exe *ex);
int		built_ins(t_tbl *cnt, t_exe *ex);

/* execute */
void	file_opener(t_exe *ex);
void	execute(void);

/* env */
int		exec_env(t_tbl *cnt, t_exe *ex);
int		env(t_tbl *tbl, t_exe *ex);

/* export */
void	env_swap(t_env **ptr_a, t_env **ptr_b);
void	sort_env(t_env **exp, int end);
int		envport(t_tbl *tbl, t_exe *ex);
int		export(t_env **env);

/* other_cmds */
void	other_cmds(t_tbl *tbl, t_exe *ex);

/* === UTILS === */

/* export_utils */
void	print_em_exps(t_env **env);
int		ft_listen(t_env	**env);
char	*chk_plus(t_exe *ex);
int		chk_append(t_env **env, t_exe *ex);

/* cd_utils */
int		cd_util(char *path);
int		cd_home(t_tbl *tbl);
int		cd_pth(t_tbl *tbl, char *path);

/* e_asterisk_utils */
int		chk_exit_arg(t_tbl *tbl, t_exe *ex);
int		exit_util(t_tbl *tbl, t_exe *ex, char *err);
int		echo_utils(char *str);

/* plumber */
void	close_sneaky_pps(t_exe *ex); //move for norm
int		creat_pps(t_pps *pps, t_exe *ex);
void	piper(t_exe *ex);
void	close_pps(t_exe *ex);

/* traffic lights */
int		cautious_close(int fd);
void	blt_chk_iof(t_tbl *tbl, t_exe *ex);
void	chk_inf_ouf(t_tbl *tbl, t_exe *ex);

/* env_utils */
int		emp_env_init(t_env **env);
size_t	env_len(char *str);
void	print_em_envs(t_env **env);
void	unset_env(t_tbl *tbl, t_exe *ex);

/* utils */
int		chk_blt(char *name, t_exe *exe);
int		giga_chad_atoi(char *str, t_exe *ex);

/* free */
void	close_fds(t_tbl *tbl, t_exe *ex);
void	parent_free_from_trouble(t_tbl *tbl, t_exe *ex);
void	free_child(t_tbl *tbl, t_exe *ex);
void	free_str(void *arg);
void	freeple(char *a, char *b, char **c, int i);

/* chd_utils */
char	**split_cmd(t_command *cmd);
int		get_cmd(char *cmd, t_pps *p);
int		get_path(t_pps *p, t_env **env);

/* err */
int		ret_perr(char *str);
int		ext_perr(char *str);
int		msg_err(char *str, int ret_val);

/* exp_unset_utils */
int		name_snatcher(char *str, t_exe *ex);
int		err_msg_env(t_exe *ex);

/* patience */
void	patience(t_exe *ex, t_tbl *tbl);

/* close_the_door */
void	blt_chk_cls(t_tbl *tbl, t_exe *ex, int *std);
void	close_fds(t_tbl *tbl, t_exe *ex);
void	close_pps(t_exe *ex);
void	close_other_pps(t_exe *ex);

/* env_addition */
void	add_env(t_tbl *tbl, t_exe *ex, char *ex_un);

#endif
