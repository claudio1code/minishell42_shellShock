/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftlurker <ftlurker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:49:12 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/12 17:18:27 by ftlurker         ###   ########.fr       */
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
	if (!s1)
		i = 0;
	if (!s2)
		j = 0;
	while (s1 && s1[++i])
		new_str[i] = s1[i];
	while (s2 && s2[++j])
		new_str[i + j] = s2[j];
	new_str[i + j] = '\0';
	if (f1 && s1)
		free (s1);
	if (f2 && s2)
		free (s2);
	return (new_str);
}
