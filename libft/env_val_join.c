/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_val_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:58:43 by aikram            #+#    #+#             */
/*   Updated: 2023/03/13 19:52:32 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	judicial_department(char **s1, char *s2, int justice)
{
	if (justice > 2)
		return ;
	if (justice > 1)
		ft_cautious_free((void **)&s2);
	if (justice)
		ft_cautious_free((void **)&s1[0]);
	else
		ft_cautious_free((void **)&s2);
}

char	*env_val_rjoin(char **s1, char *s2, int justice)
{
	char	*res;
	size_t	i[2];

	res = ft_calloc(ft_strlen(*s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!res)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (s2 && s2[i[0]] != '\0')
	{
		res[i[1]] = s2[i[0]];
		i[1]++;
		i[0]++;
	}
	i[0] = 0;
	while (s1[0] && s1[0][i[0]] != '\0')
	{
		res[i[1]] = s1[0][i[0]];
		i[1]++;
		i[0]++;
	}
	res[i[1]] = '\0';
	judicial_department(s1, s2, justice);
	return (res);
}

char	*env_val_join(char **s1, char *s2, int order, int justice)
{
	char	*result;
	size_t	src_index;
	size_t	result_index;

	if (order)
		return (env_val_rjoin(s1, s2, justice));
	result = ft_calloc(ft_strlen(*s1) + ft_strlen(s2) + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	result_index = 0;
	src_index = -1;
	while (s1[0] && s1[0][++src_index] != '\0')
	{
		result[result_index] = s1[0][src_index];
		result_index++;
	}
	src_index = -1;
	while (s2 && s2[++src_index] != '\0')
	{
		result[result_index] = s2[src_index];
		result_index++;
	}
	result[result_index] = '\0';
	judicial_department(s1, s2, justice);
	return (result);
}
