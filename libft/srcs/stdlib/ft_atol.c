/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:55:08 by clados-s          #+#    #+#             */
/*   Updated: 2025/11/13 18:31:26 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_overflow_int(char *nbr)
{
	int	i;
	int	len;

	i = 0;
	while (ft_isspace(nbr[i]))
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
		i++;
	while (nbr[i] == '0')
		i++;
	len = i;
	while (nbr[len] && ft_isdigit(nbr[len]))
		len++;
	if (len <= 17)
		return (1);
	return (0);
}

long	ft_almost_atol(char *nbr)
{
	long	result;
	int		sign;
	int		i;

	i = 0;
	result = 0;
	sign = 1;
	while ((nbr[i] >= 9 && nbr[i] <= 13) || nbr[i] == 32)
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			sign = -1;
		i++;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		result = result * 10 + (nbr[i] - '0');
		i++;
	}
	return (result * sign);
}
