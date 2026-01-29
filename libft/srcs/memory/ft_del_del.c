/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 09:42:21 by cacesar-          #+#    #+#             */
/*   Updated: 2025/12/15 07:05:21 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_del_del(void**tofree)
{
	int	count;

	count = 0;
	while (tofree[count])
		ft_del(tofree[count++]);
	ft_del(tofree);
}
