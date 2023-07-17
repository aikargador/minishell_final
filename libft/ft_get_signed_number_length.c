/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_signed_number_length.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaydemir <oaydemir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 23:33:54 by oaydemir          #+#    #+#             */
/*   Updated: 2023/01/28 22:15:49 by oaydemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned short	ft_get_signed_number_length(long long number)
{
	unsigned short	length;

	if (number == 0)
		return (1);
	length = 0;
	if (number < 0)
	{
		length++;
		number *= -1;
	}
	while (number > 0)
	{
		number /= 10;
		length++;
	}
	return (length);
}
