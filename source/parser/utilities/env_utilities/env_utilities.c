/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:17:21 by aikram            #+#    #+#             */
/*   Updated: 2023/03/18 17:41:33 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"

static size_t	splt_envlen(char const *str, char c)
{
	size_t	l;

	l = 0;
	while (str[l] != '\0' && str[l] != c)
		l++;
	return (l);
}

static char	**inner_env_alloc_failure(char **result)
{
	size_t	i;

	i = 0;
	while (i < 2)
	{
		if (result[i])
			ft_cautious_free((void **)&result[i]);
		i++;
	}
	ft_very_cautious_free((void ***)&result);
	return (NULL);
}

char	**empty_result(char **result)
{
	result[1] = ft_calloc(1, sizeof(char));
	if (result[1] == NULL)
		return (inner_env_alloc_failure(result));
	return (result);
}

char	**env_split(char const *s, char c)
{
	char	**result;

	result = ft_calloc(2, sizeof(char *));
	if (result == NULL)
		return (NULL);
	result[0] = ft_substr(s, 0, splt_envlen(s, c));
	if (result[0] == NULL)
		return (inner_env_alloc_failure(result));
	if (s[splt_envlen(s, c)])
	{
		if (s[splt_envlen(s, c) + 1])
		{
			result[1] = ft_substr(s, splt_envlen(s, c) + 1,
					ft_strlen(&s[splt_envlen(s, c)]));
			if (result[1] == NULL)
				return (inner_env_alloc_failure(result));
			return (result);
		}
	}
	if (s[splt_envlen(s, c)])
		return (empty_result(result));
	result[1] = NULL;
	return (result);
}
