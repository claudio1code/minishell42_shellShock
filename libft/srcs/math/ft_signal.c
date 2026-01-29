/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:28:21 by clados-s          #+#    #+#             */
/*   Updated: 2025/11/07 16:46:23 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_signal(char *nptr)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (!nptr[i])
		return (0);
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	if (nptr[i] == '+')
		i++;
	return (sign);
}
