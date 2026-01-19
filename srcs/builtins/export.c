/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:26:36 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/16 16:48:40 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_key(char *str)
{
	int	i;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static char	*get_next_var(char **env, char *last)
{
	char	*next;
	int		i;

	next = NULL;
	i = 0;
			while (env[i++])
		{
			if (!last || ft_strcmp(env[i], last) > 0)
				if (!next || ft_strcmp(env[i], next) < 0)
					next = env[i];
		}
	return (next);
}

static void	print_sort_env(t_info *info)
{
	int		count;
	int		i;
	char	*last_print;
	char	*next_print;

	count = 0;
	while (info->env[count])
		count++;
	last_print = NULL;
	i = 0;
	while (i < count)
	{
		next_print = get_next_var(info->env, last_print);
		if (next_print)
		{
			printf("declare -x %s\n", next_print);
			last_print = next_print;
		}
		i++;
	}
}

static void	process_one_export(t_info *info, char *arg)
{
	char	*equal;
	char	*key;
	char	*val;

	if (!is_valid_key(arg))
	{
		printf("minishell: export: '%s': not a valid indentifier", arg);
	}
	equal = ft_strchr(arg, '=');
	if (equal)
	{
		key = ft_substr(arg, 0, equal - arg);
		val = ft_strdup(equal + 1);
		update_env(info, key, val, 0);
		free(key);
	}
}

int	mini_export(t_token *token, t_info *info)
{
	int		i;

	i = 0;
	if (!token->param[i])
	{
		print_sort_env(info);
		return (0);
	}
	i = 1;
	while (token->param[i])
	{
		process_one_export(info, token->param[i]);
		i++;
	}
	return (0);
}
