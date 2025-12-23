/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:36:47 by clados-s          #+#    #+#             */
/*   Updated: 2025/12/23 10:47:12 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_cleanup(char *path)
{
	if (path)
		free(path);
}

static void	child_process(t_token *token, t_info *info)
{
	char	*path;

	if (handle_redirections(token->rdc) == -1)
		_exit(1);
	if (!token->param || !token->param[0])
		_exit(0);
	path = get_cmd_path(token->param[0], info->env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->param[0], 2);
		ft_putendl_fd(": command not found", 2);
		_exit(127);
	}
	execve(path, token->param, info->env);
	perror("execve");
	child_cleanup(path);
	_exit(1);
}

void	exec_cmd(t_token *token, t_info *info)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		child_process(token, info);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		info->exit_code = WEXITSTATUS(status);
}
