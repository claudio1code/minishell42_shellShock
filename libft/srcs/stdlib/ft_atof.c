/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:30:00 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/24 11:25:26 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	after_dot(char *nptr)
{
	double	fracttion_power;
	double	result;
	int		i;

	i = 0;
	result = 0.0;
	while (nptr[i] && nptr[i] != '.')
		i++;
	if (nptr[i] == '.')
	{
		i++;
		fracttion_power = 0.1;
		while (ft_isdigit(nptr[i]))
		{
			result += (nptr[i] - '0') * fracttion_power;
			fracttion_power /= 10.0;
			i++;
		}
	}
	return (result);
}

double	ft_atof(char *nptr)
{
	double	result;
	double	nbr_fracttion;
	int		signal;
	int		i;

	if (ft_is_double(nptr) == 0)
		return (0.0);
	result = 0.0;
	nbr_fracttion = 0.0;
	signal = ft_signal(nptr);
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		result = (result * 10.0) + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] == '.')
		nbr_fracttion = after_dot(nptr);
	return ((result + nbr_fracttion) * (double)signal);
}
