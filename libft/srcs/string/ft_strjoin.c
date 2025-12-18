/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:49:12 by clados-s          #+#    #+#             */
/*   Updated: 2025/12/18 12:49:27 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2, int f1, int f2)
{
	char	*new_str;
	int		len_s;
	int		i;
	int		j;

	len_s = ft_strlen(s1) + ft_strlen(s2);
	new_str = malloc(len_s + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		new_str[i] = s1[i];
	while (s2[++j])
		new_str[i + j] = s2[j];
	new_str[i + j] = '\0';
	if (f1)
		free (s1);
	if (f2)
		free (s2);
	return (new_str);
}
