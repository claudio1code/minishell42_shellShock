/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:26:36 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/28 18:08:09 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* aqui a função formata a variável de ambiente no formato KEY="VALUE" */
static char	*format_var(char *key, char *value)
{
	char	*tmp;
	char	*res;

	if (!value)
		return (ft_strdup(key));
	tmp = ft_strjoin(key, "\"", 0, 0);
	res = ft_strjoin(tmp, value, 1, 0);
	tmp = ft_strjoin(res, "\"", 1, 0);
	return (tmp);
}
/* essa função converte a hashtable em um array de strings formatadas */
static char **hash_to_array(t_hashtable *env)
{
	char		**array;
	t_env_node	*node;
	int			i;
	int			j;

	array = ft_calloc(sizeof(char *), (count_vars(env) + 1));
	if (!array)
		return (NULL);
	i = 0;
	j = 0;
	while (i < TABLE_SIZE)
	{
		node = env->buckets[i];
		while (node)
		{
			if (ft_strcmp(node->key, "_") != 0)
				array[j++] = format_var(node->key, node->value);
			node = node->next;
		}
		i++;
	}
	array[j] = NULL;
	return (array);
}
/* essa função ordena o array de variáveis de ambiente */
static void	bublle_sort_array(char **array)
{
	int		i;
	int		j;
	char	*swap;

	i = 0;
	while (array[i])
	{
		j = i + 1;
		while (array[j])
		{
			if (ft_strcmp(array[i], array[j]) > 0)
			{
				swap = array[i];
				array[i] = array[j];
				array[j] = swap;
			}
			j++;
		}
		i++;
	}
}

/* essa função atualiza ou adiciona uma variável de ambiente */
static void	export_var(char *arg, t_hashtable *env)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		key = ft_substr(arg, 0, equal_sign - arg);
		value = ft_strdup(equal_sign + 1);
		if (!ft_isalpha(key[0]) && key[0] != '_')
		{
			err_invalid_export(arg, key, value);
			return ;
		}
		update_hash(env, key, value);
		free(key);
		free(value);
	}
	else
	{
		if (!get_env_val(env, arg))
			update_hash(env, arg, NULL);
	}
}

int	mini_export(t_token *token, t_info *info)
{
	char	**sorted_env;
	int		i;

	if (!token->param[1])
	{
		sorted_env = hash_to_array(info->env);
		bublle_sort_array(sorted_env);
		i = 0;
		while (sorted_env[i])
		{
			printf("declare -x %s\n", sorted_env[i]);
			free(sorted_env[i]);
			i++;
		}
		free(sorted_env);
		return (0);
	}
	else
	{
		i = 0;
		while (token->param[++i])
			export_var(token->param[i], info->env);
	}
	return (0);
}
