/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:16:06 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/27 15:19:54 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_hashtable(t_hashtable *table)
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
		free_hashtable(info->env);
	// if (info->l);
	// 	free(info->l);
	if (info->str)
		free(info->str);
	rl_clear_history();
}

/* Printa erro de argumento não numérico */
void	err_numeric(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
}
