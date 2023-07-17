/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 23:49:53 by oaydemir          #+#    #+#             */
/*   Updated: 2023/03/11 16:58:17 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	src_index;
	char	*result;
	size_t	result_index;

	result = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	result_index = 0;
	src_index = 0;
	while (s1 && s1[src_index] != '\0')
	{
		result[result_index] = s1[src_index];
		result_index++;
		src_index++;
	}
	src_index = 0;
	while (s2 && s2[src_index] != '\0')
	{
		result[result_index] = s2[src_index];
		result_index++;
		src_index++;
	}
	result[result_index] = '\0';
	return (result);
}
