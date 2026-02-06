/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:36:47 by clados-s          #+#    #+#             */
/*   Updated: 2026/02/06 11:32:46 by claudio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*função auxiliar na limpeza da string dos paths*/
static void	finish_process(t_token *token, t_info *info)
{
	int	exit_code;

	exit_code = 0;
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
		exit_code = info->exit_code;
		clean_shell(info);
		exit(exit_code);
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

static int	exit_code_cmd(t_info *info, int status)
{
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			status = 130;
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putendl_fd("Quit (core dumped)", 2);
			status = 131;
		}
	}
	signal(SIGINT, signaler);
	clean_shell(info);
	return (status);
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
		signal(SIGINT, signaler);
		return (1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_process_exec(token, info);
	}
	waitpid(pid, &status, 0);
	return (exit_code_cmd(info, status));
}
