/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:06:44 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/22 14:02:30 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long	number;

	number = ft_atol((char *)nptr);
	if (number >= INT_MAX)
		return (INT_MAX);
	else if (number <= INT_MIN)
		return (INT_MIN);
	return (number);
}
