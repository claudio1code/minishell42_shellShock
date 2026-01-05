/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:08:37 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/05 14:42:07 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtins(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	return (0);
}

int	exec_bultin(t_token *token)
{
	char	*cmd;

	cmd = token->param[0];
	if (ft_strncmp(cmd, "echo", 5))
		return (mini_echo(token));
	return (0);
}
