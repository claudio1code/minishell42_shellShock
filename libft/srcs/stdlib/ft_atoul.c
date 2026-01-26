/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:52:29 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/22 16:05:34 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long	ft_atoul(char *nptr)
{
	unsigned long	result;
	int				i;

	result = 0;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (result > ULONG_MAX / 10 || (result == ULONG_MAX / 10
				&& (nptr[i] - '0') > ULONG_MAX % 10))
			return (ULONG_MAX);
		result = (result * 10) + (nptr[i++] - '0');
	}
	return (result);
}
