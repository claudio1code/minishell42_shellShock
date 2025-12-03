/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:06:44 by clados-s          #+#    #+#             */
/*   Updated: 2025/11/15 13:46:55 by claudio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long	number;

	number = ft_almost_atol((char *)nptr);
	if (number >= INT_MAX)
		return (INT_MAX);
	else if (number <= INT_MIN)
		return (INT_MIN);
	return (number);
}
