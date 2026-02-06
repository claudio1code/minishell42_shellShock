/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:51:03 by clados-s          #+#    #+#             */
/*   Updated: 2026/02/06 19:33:44 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_heredoc(char *delimiter)
{
	ft_putstr_fd("warning: here-document at line 1 delimited by", 2);
	ft_putstr_fd("end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

void	error_dir(t_token *token, t_info *info)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(token->param[0], 2);
	ft_putstr_fd(": Is a directory", 2);
	ft_putstr_fd("\n", 2);
	clean_shell(info);
	exit(126);
}

void	error_no_such(t_token *token, t_info *info)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(token->param[0], 2);
	ft_putstr_fd(": No such file or directory", 2);
	ft_putstr_fd("\n", 2);
	clean_shell(info);
	exit(127);
}

void	cleanup_heredocs(t_token *token)
{
	int	i;

	while (token)
	{
		i = 0;
		while (token->rdc && token->rdc[i])
		{
			if (!ft_strncmp(token->rdc[i], "<", 2)
				&& !ft_strncmp(token->rdc[i + 1], ".heredoc_", 9))
			{
				unlink(token->rdc[i + 1]);
			}
			i += 2;
		}
		token = token->next;
	}
}
