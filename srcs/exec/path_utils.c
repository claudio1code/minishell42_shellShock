/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:44:05 by clados-s          #+#    #+#             */
/*   Updated: 2026/02/04 11:56:04 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//auxiliar para casos de caminho absoluto
static char	*check_absolut_path(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

/*Essa função, checa primeiro se é o caminho absoluto,
se não for, ele busca os paths dos binários dos comandos */
char	*get_cmd_path(char *cmd, t_hashtable *env)
{
	char	**paths;
	char	*path_part;
	char	*full_path;
	char	*path_env;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (check_absolut_path(cmd));
	path_env = get_env_val(env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = -1;
	while (paths[++i])
	{
		path_part = ft_strjoin(paths[i], "/", 0, 0);
		full_path = ft_strjoin(path_part, cmd, 1, 0);
		if (!access(full_path, X_OK))
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
	}
	return (free_split_null(paths));
}
