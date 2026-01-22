/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:04:58 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/20 14:18:43 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_env_var(t_info *info, int index)
{
	int	i;

	free (info->env[index]);
	i = index;
	while (info->env[i])
	{
		info->env[i] = info->env[i + 1];
		i++;
	}
}

int	mini_unset(t_token *token, t_info *info)
{
	int		i;
	int		j;
	int		len;
	char	*key;

	i = 1;
	while (token->param[i])
	{
		key = token->param[i];
		len = ft_strlen(key);
		j = 0;
		while (info->env)
		{
			if ((ft_strncmp(info->env[j], key, len))
				&& (info->env[j][len] == '=' || !info->env[j][len]))
			{
				remove_env_var(info, j);
				break;
			}
			j++;
		}
		i++;
	}
	return (0);
}