/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:40:45 by clados-s          #+#    #+#             */
/*   Updated: 2025/12/22 11:56:11 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_file(char *file, char *mode)
{
	int	fd;

	fd = -1;
	if (!ft_strncmp(mode, "<", 2))
		fd = open(file, O_RDONLY);
	else if (!ft_strncmp(mode, ">", 2))
		fd = open(file, (O_WRONLY | O_CREAT | O_TRUNC | 0644));
	else if (!ft_strncmp(mode, ">>", 3))
		fd = open(file, (O_WRONLY | O_CREAT | O_APPEND | 0644));
	if (fd == -1)
		perror(file);
	return (fd);
}

int	handle_redirections(char **redir)
{
	int	i;
	int	fd;

	if (!redir)
		return (0);
	i = 0;
	while (redir[i])
	{
		if (!redir[i + 1])
			break ;
		fd = open_file(redir[i + 1], redir[i]);
		if (fd == -1)
			return (-1);
		if (!ft_strncmp(redir[i], "<", 1))
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		i += 2; //ex: matriz [0| >]->[1| out]->[2| <]->.[3| in]
	}
	return (0);
}
