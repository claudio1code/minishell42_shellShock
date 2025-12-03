/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:18:14 by clados-s          #+#    #+#             */
/*   Updated: 2025/10/21 18:32:02 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_double(char *nptr)
{
	int	dot_count;
	int	i;

	i = 0;
	dot_count = 0;
	if ((nptr[i] == '-' && ft_isdigit(nptr[i + 1]))
		|| (nptr[i] == '+' && ft_isdigit(nptr[i + 1])))
		i++;
	while (nptr[i])
	{
		if (nptr[i] == '.')
			dot_count++;
		if (nptr[i] == '.' || ft_isdigit(nptr[i]))
			i++;
		else
			return (0);
	}
	if (dot_count > 1)
		return (0);
	if (dot_count == 0)
		return (1);
	if (nptr[0] == '.' || nptr[i - 1] == '.')
		return (0);
	return (2);
}
