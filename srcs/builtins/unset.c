/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:04:58 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/22 12:14:20 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*essa função remove um nó da tabela hash, ela vai percorrer
a linka de list olhando se a key é igual a key passada, se for
atualiza a tabela, da free do nó removido e do valor associado,
decrementa o contador de elementos da tabela*/
static void	del_node(t_hashtable *table, char *key)
{
	unsigned long	idx;
	t_env_node		*current;
	t_env_node		*prev;

	idx = ft_hashtable(key);
	current = table->buckets[idx];
	prev = NULL;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			if (prev)
				prev->next = current->next;
			else
				table->buckets[idx] = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			table->count--;
			return;
		}
		prev = current;
		current = current->next;
	}
}

int	mini_unset(t_token *token, t_info *info)
{
	int	i;

	i = 1;
	while (token->param[i])
	{
		del_node(info->env, token->param[i]);
		i++;
	}
	return (0);
}
