/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:05:46 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/22 14:06:16 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isint(char *nptr)
{
	long long	number;

	if (!nptr || !*nptr)
		return (0);
	if (!ft_overflow_int(nptr))
		return (0);
	number = ft_atol(nptr);
	if (number <= INT_MAX && number >= INT_MIN)
		return (1);
	return (0);
}
