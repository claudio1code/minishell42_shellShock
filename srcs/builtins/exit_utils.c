/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:16:06 by clados-s          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/02/04 15:14:14 by clados-s         ###   ########.fr       */
=======
/*   Updated: 2026/02/04 12:17:25 by cacesar-         ###   ########.fr       */
>>>>>>> correção_de_expansão
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/* Libera a memória ocupada pela hashtable, que 
são os nós e os valores das variaveis*/

void	*free_hashtable(t_hashtable *table)
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
	if (info->env)
		info->env = (t_hashtable *)free_hashtable(info->env);
	if (info->exec)
		info->exec = clean_token(info->exec);
	if (info->pid)
		free(info->pid);
	if (info->in_backup != -1)
		close(info->in_backup);
	if (info->out_backup != -1)
		close(info->out_backup);
	free(info);
	rl_clear_history();
}

void	*clean_token(t_token**r)
{
	t_token	**r2;
	t_token	*tmp;
	int		c1;

	c1 = -1;
	r2 = r;
	while (r2[++c1])
	{
		tmp = r2[c1]->next;
		while (r2[c1])
		{
			if (r2[c1]->cmd)
				free(r2[c1]->cmd);
			if (r2[c1]->rdc)
				ft_del_del((void **)r2[c1]->rdc);
			if (r2[c1]->param)
				ft_del_del((void **)r2[c1]->param);
			free(r2[c1]);
			r2[c1] = tmp;
			if (r2[c1])
				tmp = r2[c1]->next;
		}
	}
	ft_del_del((void **)r);
	return (0);
}
