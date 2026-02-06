/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:44:05 by clados-s          #+#    #+#             */
/*   Updated: 2026/02/06 19:32:55 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//auxiliar para casos de caminho absoluto
static char	*check_absolut_path(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	else if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*find_exec_in_paths(char **paths, char *cmd)
{
	char	*path_part;
	char	*full_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		path_part = ft_strjoin(paths[i], "/", 0, 0);
		full_path = ft_strjoin(path_part, cmd, 1, 0);
		if (!access(full_path, X_OK))
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

/*Essa função, checa primeiro se é o caminho absoluto,
se não for, ele busca os paths dos binários dos comandos */
char	*get_cmd_path(char *cmd, t_hashtable *env)
{
	char	**paths;
	char	*full_path;
	char	*path_env;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (check_absolut_path(cmd));
	path_env = get_env_val(env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	full_path = find_exec_in_paths(paths, cmd);
	free_split(paths);
	return (full_path);
}

int	is_parent_builtin(t_token *token)
{
	if (!token->param || !token->param[0])
		return (0);
	if (!ft_strncmp(token->param[0], "cd", 3)
		|| !ft_strncmp(token->param[0], "export", 7)
		|| !ft_strncmp(token->param[0], "unset", 6)
		|| !ft_strncmp(token->param[0], "exit", 5))
		return (1);
	return (0);
}
