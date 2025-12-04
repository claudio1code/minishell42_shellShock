/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:49:12 by clados-s          #+#    #+#             */
/*   Updated: 2025/12/04 15:34:45 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*new_str;
	int		len_s;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
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
	free (s1);
	return (new_str);
}
