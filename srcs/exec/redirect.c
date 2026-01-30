/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:40:45 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/30 16:43:25 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Aqui eu cuido da abertura dos fd dos redirects e 
as permissões que cada um precisa*/
static int	open_file(char *file, char *mode)
{
	int	fd;

	fd = -1;
	if (!ft_strncmp(mode, "<", 2))
		fd = open(file, O_RDONLY);
	else if (!ft_strncmp(mode, ">", 2))
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strncmp(mode, ">>", 3))
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		perror(file);
	return (fd);
}

/*aqui eu trato os redirects, percorro a matriz de redirecionamentos
e trato cada um, os de input eu faço um dup pra stdin e os de output
eu faço um dup pra stdout e vou incrementando de 2 em 2 pra ir pegando
só os redirects*/
int	handle_redirections(t_token *token)
{
	int	i;
	int	fd;

	if (!token->rdc)
		return (0);
	i = 0;
	while (token->rdc[i])
	{
		if (!token->rdc[i + 1])
			break ;
		fd = open_file(token->rdc[i + 1], token->rdc[i]);
		if (fd == -1)
			return (-1);
		if (!ft_strncmp(token->rdc[i], "<", 2))
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		i += 2; //ex: matriz [0| >]->[1| out]->[2| <]->.[3| in]
	}
	return (0);
}

