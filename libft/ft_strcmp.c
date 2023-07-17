/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:12:07 by oaydemir          #+#    #+#             */
/*   Updated: 2023/01/28 22:16:28 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *str1, char *str2)
{
	int		index;

	index = 0;
	while (str1[index] != '\0' && str2[index] != '\0')
	{
		if (str1[index] != str2[index])
			break ;
		index++;
	}
	return (str1[index] - str2[index]);
}
