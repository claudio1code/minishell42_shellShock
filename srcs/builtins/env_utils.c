/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:05:29 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/28 17:12:00 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Busca o valor relacionado a uma chave no ambiente,
percorro a hashtable até encontrar a chave*/
char	*get_env_val(t_hashtable *env, char *key)
{
	unsigned long	idx;
	t_env_node		*tmp;

	idx = ft_hashtable(key);
	tmp = env->buckets[idx];
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

/* Converte a hashtable para char ** (formato KEY=VALUE) para o execve 
que só aceita um (const char *arg[])*/
char	**ht_to_matrix(t_hashtable *env)
{
	char		**matrix;
	t_env_node	*tmp;
	int			i;
	int			j;

	matrix = ft_calloc(sizeof(char *) , (env->count + 1));
	if (!matrix)
		return (NULL);
	i = 0;
	j = 0;
	while (i < TABLE_SIZE)
	{
		tmp = env->buckets[i];
		while (tmp)
		{
			if (tmp->value)
				matrix[j] = ft_triple_strjoin(tmp->key, "=", tmp->value); 
			else
				matrix[j] = ft_strjoin(tmp->key, "=", 0, 0);
			j++;
			tmp = tmp->next;
		}
		i++;
	}
	return (matrix);
}

int	count_vars(t_hashtable *env)
{
	return (env->count);
}
