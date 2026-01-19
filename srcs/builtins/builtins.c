/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:08:37 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/15 14:41:51 by clados-s         ###   ########.fr       */
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

int	exec_bultin(t_token *token, t_info *info)
{
	char	*cmd;

	cmd = token->param[0];
	if (!ft_strncmp(cmd, "echo", 5))
		return (mini_echo(token));
	if (!ft_strncmp(cmd, "cd", 3))
		return (mini_cd(info, token));
	if (!ft_strncmp(cmd, "pwd", 4))
		return (pwd(token));
	if (!ft_strncmp(cmd, "export", 7))
		return (mini_export(token, info));
	return (0);
}

