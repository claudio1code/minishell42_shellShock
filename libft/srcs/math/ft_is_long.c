/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:50:16 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/22 16:11:06 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_long(char *nptr)
{
	unsigned long	nbr;

	nbr = ft_atoul(nptr);
	if (nbr <= LONG_MAX)
		return (1);
	return (0);
}
