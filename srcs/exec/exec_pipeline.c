/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 19:04:49 by claudio           #+#    #+#             */
/*   Updated: 2025/12/29 14:54:46 by claudio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_one(t_logic *node, t_info *info, int fd[2]) 
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	exec_tree(node->left, info);
	exit(EXIT_FAILURE);
}

static void	child_two(t_logic *node, t_info *info, int fd[2])
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	exec_tree(node->right, info);
	exit(EXIT_FAILURE);
}

static void	parent_process(t_logic *node, t_info *info, int fd[2])
{
	pid_t	pid1;
	pid_t	pid2;
	int 	status;

	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
		child_one(node, info, fd);
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
		child_two(node, info, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}
static void	exec_pipe(t_logic *node, t_info *info)
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
	int		status;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	parent_process(node, info, fd);
}
void exec_tree(t_logic *node, t_info *info)
{
	pid_t	pid;
	
	
	if (!node)
		return ;
	if (node->operator && !ft_strncmp(node->operator, "|", 2))
		exec_pipe(node, info);
	else
		exec_cmd(node->cmd, info);
}
