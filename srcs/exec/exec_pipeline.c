/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 19:04:49 by claudio           #+#    #+#             */
/*   Updated: 2026/02/06 19:34:16 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parent_process(int fd[2], int *prev_fd)
{
	close(fd[1]);
	if (*prev_fd != -1)
		close(*prev_fd);
	*prev_fd = fd[0];
}

static void	wait_children(t_info *info, pid_t last_pid)
{
	int		status;
	int		last_status;
	pid_t	pid;

	last_status = 0;
	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid <= 0)
			break ;
		if (pid == last_pid)
			last_status = status;
	}
	if (WIFEXITED(last_status))
		info->exit_code = WEXITSTATUS(last_status);
	else if (WIFSIGNALED(last_status))
		info->exit_code = 128 + WTERMSIG(last_status);
}

static void	child_process(t_token *token, t_info *info, int fd[2], int prev_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (token->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	exit(exec_cmd(token, info));
}

static void	loop_pipeline(t_token *token, t_info *info)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	pid = 0;
	while (token)
	{
		if (token->next && pipe(fd) == -1)
			return (perror("pipe"));
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid == 0)
			child_process(token, info, fd, prev_fd);
		if (token->next)
			parent_process(fd, &prev_fd);
		else if (prev_fd != -1)
			close(prev_fd);
		token = token->next;
	}
	wait_children(info, pid);
}

void	exec_pipeline(t_token *token, t_info *info)
{
	if (prepare_heredocs(token) == -1)
	{
		info->exit_code = 130;
		cleanup_heredocs(token);
		return ;
	}
	if (error(token))
	{
		cleanup_heredocs(token);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (token && !token->next && !token->prev && is_parent_builtin(token))
		exec_cmd(token, info);
	else
		loop_pipeline(token, info);
	signal(SIGINT, signaler);
	cleanup_heredocs(token);
}
