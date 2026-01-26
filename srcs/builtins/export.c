/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:26:36 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/26 15:02:48 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_vars(t_hashtable *env)
{
	return (env->count);
}

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

int	mini_export(t_token *token, t_info *info)
{
	char	**sorted_env;
	int		i;

	if (!token->param[i])
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
	return (0);
}
