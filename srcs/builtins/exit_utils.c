/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:16:06 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/29 18:43:09 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Libera a memória ocupada pela hashtable, que 
são os nós e os valores das variaveis*/
int	free_hashtable(t_hashtable *table)
{
	int			i;
	t_env_node	*tmp;
	t_env_node	*next;

	i = 0;
	while (i < TABLE_SIZE)
	{
		tmp = table->buckets[i];
		while (tmp)
		{
			next = tmp->next;
			free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			tmp = next;
		}
		i++;
	}
	free(table);
	return (0);
}

int	is_numeric_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	clean_shell(t_info *info)
{
	info->env = free_hashtable(info->env);
	info->exec = clean_token(info->exec);
	free(info);
	rl_clear_history();
}

int	clean_token(t_token**r)
{
	t_token	**r2;
	int		c1;

	c1 = -1;
	r2 = r;
	while (r2[++c1])
	{
		while (r2[c1])
		{
			if (r2[c1]->cmd)
				free(cmd);
			if (r2[c1]->rdc)
				ft_del_del(r2[c1]->rdc);
			if (r2[c1]->param)
				ft_del_del(r2[c1]->param);
			r2[c1] = r2[c1]->next;
		}
	}
	ft_del_del(r2);
	return (0);
}
