/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_care.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:03:06 by aikram            #+#    #+#             */
/*   Updated: 2023/03/15 19:49:31 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

char	**split_cmd(t_command *cmd)
{
	char	**str;
	int		i[2];
	int		l;

	l = 0;
	i[0] = -1;
	str = NULL;
	while (cmd->arguments[++i[0]] != NULL)
		if (cmd->arguments[i[0]][0])
			l++;
	str = ft_calloc(l + 2, sizeof(char *));
	if (!str)
		return (NULL);
	i[0] = 0;
	i[1] = -1;
	str[i[0]++] = ft_strdup(cmd->name);
	while (cmd->arguments[++i[1]])
		if (cmd->arguments[i[1]][0])
			str[i[0]++] = ft_strdup(cmd->arguments[i[1]]);
	str[i[0]] = NULL;
	return (str);
}

int	get_path(t_pps *p, t_env **env)
{
	t_env	*node;

	if (!env || !*env)
		node = NULL;
	else
		node = *env;
	while (node && ft_strncmp("PATH", node->name, 5) != 0)
		node = node->nxt;
	if (!node)
		return (1);
	p->pths = ft_split(node->vals, ':');
	return (0);
}

int	get_cmd(char *cmd, t_pps *p)
{
	int		i;

	if (p->pth_tkn || cmd[0] == '/' || ((!(strncmp("./", cmd, 2)) || \
		!(strncmp("../", cmd, 3))) && !access(cmd, X_OK)))
	{
		p->cmd_pth = ft_strdup(cmd);
		return (1);
	}
	i = -1;
	while (p->pths[++i])
	{
		p->cmd_pth = env_val_join(&p->pths[i], "/", 0, 3);
		if (!p->cmd_pth)
			return (0);
		p->cmd_pth = env_val_join(&p->cmd_pth, cmd, 0, 1);
		if (!p->cmd_pth)
			return (0);
		if (!access(p->cmd_pth, X_OK))
			return (1);
		ft_cautious_free((void **)&p->cmd_pth);
	}
	return (0);
}
