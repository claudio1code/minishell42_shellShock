/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triple_strjoin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:29:11 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/26 15:44:16 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_triple_strjoin(char *s1, char *s2, char *s3)
{
	char	*new_str;
	char	*tmp;

	tmp = ft_strjoin(s1, s2, 0, 0);
	new_str = ft_strjoin(tmp, s3, 1, 0);
	return (new_str);
}
