/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atold.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 09:12:10 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/22 10:04:45 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long double	after_dot(char *nptr)
{
	long double	fracttion_power;
	long double	result;
	int			i;

	i = 0;
	result = 0.0L;
	while (nptr[i] && nptr[i] != '.')
		i++;
	if (nptr[i] == '.')
	{
		i++;
		fracttion_power = 0.1L;
		while (ft_isdigit(nptr[i]))
		{
			result += (nptr[i] - '0') * fracttion_power;
			fracttion_power /= 10.0L;
			i++;
		}
	}
	return (result);
}

long double	ft_atold(char *nptr)
{
	long double	result;
	long double	nbr_fracttion;
	int			signal;
	int			i;

	if (ft_is_double(nptr) == 0)
		return (0.0L);
	result = 0.0L;
	nbr_fracttion = 0.0L;
	signal = ft_signal(nptr);
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		result = (result * 10.0L) + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] == '.')
		nbr_fracttion = after_dot(nptr);
	return ((result + nbr_fracttion) * (long double)signal);
}
