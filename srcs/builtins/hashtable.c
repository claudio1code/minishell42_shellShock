/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:09:07 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/29 11:27:58 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*essa função vai criar uma especie de ID da key, eu utilizo o 
algoritmo djb2 que pega uma hash com valor de número primo para evitar
colisões e retorna o índice da tabela hash, mutiplico cada caracter 
da key(ex: "HOME") por 33 e faço módulo do tamanho da tabela */
unsigned long	ft_hashtable(char *key)
{
	unsigned long	hash;
	int				c;
	int				i;

	hash = 5381;
	i = 0;
	while (key[i])
	{
		c = key[i];
		hash = ((hash << 5) + hash) + c;
		i++;
	}
	return (hash % TABLE_SIZE);
}

/* cria um novo nó de ambiente e retorna um ponteiro para ele */
t_env_node	*new_env_node(char *key, char *value)
{
	t_env_node	*node;

	node = ft_calloc(1, sizeof(t_env_node));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

/* substitui o valor de um nó existente */
static void	replace_value(t_env_node *tmp, char *value)
{
	if (tmp->value)
		free(tmp->value);
	tmp->value = ft_strdup(value);
}

/* atualiza o valor de um nó existente ou adiciona um novo nó,
entao ele vai ver no buckets da table se já existe uma key igual, 
se não, ele adiciona um novo nó e atualiza a tabela e o contador,
que guarda quantas chaves existem na tabela*/
void	update_hash(t_hashtable *table, char *key, char *value)
{
	unsigned long	idx;
	t_env_node		*tmp;
	t_env_node		*prev;
	
	idx = ft_hashtable(key);
	tmp = table->buckets[idx];
	prev = NULL;

	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (value)
				replace_value(tmp, value);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev)
		prev->next = new_env_node(key, value);
	else
		table->buckets[idx] = new_env_node(key, value);
	table->count++;
}

/* inicializa a tabela de ambiente com os valores do envp */
void	init_env_table(t_info *info, char **envp)
{
	int		i;
	char	*key;
	char	*val;
	char	*eq;

	info->env = ft_calloc(1, sizeof(t_hashtable));
	if (!info->env)
		return ;
	i = 0;
	while (envp[i])
	{
		eq = ft_strchr(envp[i], '=');
		if (eq)
		{
			key = ft_substr(envp[i], 0, eq - envp[i]);
			val = ft_strdup(eq + 1);
			update_hash(info->env, key, val);
			free(key);
			free(val);
		}
		i++;
	}
}
