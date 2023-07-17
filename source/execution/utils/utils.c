/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:03:02 by aikram            #+#    #+#             */
/*   Updated: 2023/03/19 02:59:13 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	blt_tkn(t_exe *exe, int tkn)
{
	exe->b_tkn = tkn;
	return (1);
}

int	chk_blt(char *name, t_exe *exe)
{
	if (!ft_strncmp(name, "echo", 5))
		return (blt_tkn(exe, 0));
	else if (!ft_strncmp(name, "cd", 3))
		return (blt_tkn(exe, 1));
	else if (!ft_strncmp(name, "pwd", 4))
		return (blt_tkn(exe, 2));
	else if (!ft_strncmp(name, "export", 7))
		return (blt_tkn(exe, 3));
	else if (!ft_strncmp(name, "unset", 6))
		return (blt_tkn(exe, 4));
	else if (!ft_strncmp(name, "env", 4))
		return (blt_tkn(exe, 5));
	else if (!ft_strncmp(name, "exit", 5))
		return (blt_tkn(exe, 69));
	return (-1);
}

unsigned long long	chk_len(unsigned long long num, int s)
{
	unsigned long long	i;

	i = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num /= 10;
		i++;
	}
	if (s == -1)
		i++;
	return (i);
}

int	giga_chad_atoi(char *str, t_exe *ex)
{
	unsigned long long	r;
	unsigned long long	i;
	int					s;

	s = 1;
	i = 0;
	r = 0;
	ex->bad_no = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			s *= -1;
	while (str[i] >= '0' && str[i] <= '9')
		r = r * 10 + str[i++] - '0';
	while (*(str + i) == ' ')
		str++;
	if ((r > LLONG_MAX && s == 1) || (r > (LLONG_MAX + 1ULL) && s == -1) \
		|| str[i] || chk_len(r, s) != i)
		return (1);
	ex->bad_no = 0;
	return (r * s);
}
