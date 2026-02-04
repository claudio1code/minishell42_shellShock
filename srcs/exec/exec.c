/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:36:47 by clados-s          #+#    #+#             */
/*   Updated: 2026/02/04 17:54:23 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*função auxiliar na limpeza da string dos paths*/
static void	finish_process(t_token *token, t_info *info)
{
	if (handle_redirections(token) == -1)
	{
		clean_shell(info);
		exit(1);
	}
	if (!token->param || !token->param[0])
	{
		clean_shell(info);
		exit(0);
	}
	if (is_builtins(token->param[0]))
	{
		info->exit_code = exec_bultin(token, info);
		clean_shell(info);
		exit(info->exit_code);
	}
}

/*Função auxiliar da execução, ele verifica se os fd do 
redirects falharam, se é bultin ou comando binário, se for builtin 
ele chama a função exec_builtin, caso contrario ele vai buscar o path
do cmd, se não achar nas pastas bin, retorna "command not found" e se
encontrar, chama o execve que que executa um novo programa a partir 
de um processo já existente.*/
static void	child_process_exec(t_token *token, t_info *info)
{
	char	*path;
	char	**env_matrix;

	finish_process(token, info);
	path = get_cmd_path(token->param[0], info->env);
	if (!path)
		print_erro(token, info);
	env_matrix = ht_to_matrix(info->env);
	execve(path, token->param, env_matrix);
	perror("execve");
	if (path)
		free(path);
	free_split(env_matrix);
	clean_shell(info);
	exit(1);
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

static void	exec_parent_builtin(t_token *token, t_info *info)
{
	info->in_backup = dup(STDIN_FILENO);
	info->out_backup = dup(STDOUT_FILENO);
	if (handle_redirections(token) == -1)
	{
		info->exit_code = 1;
		dup2(info->in_backup, STDIN_FILENO);
		dup2(info->out_backup, STDOUT_FILENO);
		close(info->in_backup);
		close(info->out_backup);
		return ;
	}
	info->exit_code = exec_bultin(token, info);
	dup2(info->in_backup, STDIN_FILENO);
	dup2(info->out_backup, STDOUT_FILENO);
	close(info->in_backup);
	close(info->out_backup);
}

/*Executa os comandos, faz um fork no processo pai
e se for bem sucessedido ele chama o child_process_exec e 
guarda o status de saída, guandando na variavel exit_code*/
int	exec_cmd(t_token *token, t_info *info)
{
	pid_t	pid;
	int		status;

	if (is_parent_builtin(token) && !token->next
		&& !token->prev && is_parent_builtin(token))
	{
		exec_parent_builtin(token, info);
		return (0);
	}
	pid = fork();
	g_sig = (int)pid;
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		child_process_exec(token, info);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signaler(-42);
	if (WIFEXITED(status))
		info->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		info->exit_code = 128 + WTERMSIG(status);
	clean_shell(info);
	return (status);
}
