/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:25:04 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/22 11:44:12 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*printa todas as variáveis de ambiente se o valor for válido
ele printa, se não vai para o próximo bucket*/
int	mini_env(t_info *info)
{
	int			i;
	t_env_node	*tmp;

	i = 0;
	while (i < TABLE_SIZE)
	{
		tmp = info->env->buckets[i];
		while (tmp)
		{
			if (tmp->value)
				printf("%s=%s\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
