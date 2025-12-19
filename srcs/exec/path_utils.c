/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:40:42 by clados-s          #+#    #+#             */
/*   Updated: 2025/12/18 14:49:03 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_part;
	char	*full_path;
	int		i;

	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		return (NULL);
	paths = ft_split(*envp + 5, ':');
	i = 0;
	while (paths[i])
	{
		path_part = ft_strjoin(paths[i], "/", 1, 0);
		full_path = ft_strjoin(path_part, cmd, 1, 0);
		if (!access(full_path, X_OK))
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (free_split_null(paths));
}

