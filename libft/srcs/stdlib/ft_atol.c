/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:55:08 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/22 14:06:04 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(char *str)
{
	long	res;
	int		sign;
	int		i;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > LONG_MAX / 10 || (res == LONG_MAX / 10
				&& (str[i] - '0') > LONG_MAX % 10))
		{
			if (sign == 1)
				return (LONG_MAX);
			return (LONG_MIN);
		}
		res = (res * 10) + (str[i++] - '0');
	}
	return (res * sign);
}
