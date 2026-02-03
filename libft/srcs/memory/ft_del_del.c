/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 09:42:21 by cacesar-          #+#    #+#             */
/*   Updated: 2026/02/03 11:50:25 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_del_del(void**tofree)
{
	int	count;

	count = 0;
	if (!tofree)
		return ;
	while (tofree[count])
		ft_del(tofree[count++]);
	ft_del(tofree);
}
