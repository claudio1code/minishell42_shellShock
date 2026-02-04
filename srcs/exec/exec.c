/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:36:47 by clados-s          #+#    #+#             */
/*   Updated: 2026/02/03 19:00:50 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*função auxiliar na limpeza da string dos paths*/
void	child_cleanup(char *path)
{
	if (path)
		free(path);
}

/*Função auxiliar da execução, ele verifica se os fd do 
redirects falharam, se é bultin ou comando binário, se for builtin 
ele chama a função exec_builtin, caso contrario ele vai buscar o path
do cmd, se não achar nas pastas bin, retorna "command not found" e se
encontrar, chama o execve que que executa um novo programa a partir 
de um processo já existente.*/
static void	child_process(t_token *token, t_info *info)
{
	char	*path;
	char	**env_matrix;

	if (handle_redirections(token) == -1)
		exit(1);
	if (!token->param || !token->param[0])
		exit(0);
	if (is_builtins(token->param[0]))
	{
		info->exit_code = exec_bultin(token, info);
		exit(info->exit_code);
	}
	path = get_cmd_path(token->param[0], info->env);
	if (!path)
		print_erro(token);
	env_matrix = ht_to_matrix(info->env);
	execve(path, token->param, env_matrix);
	perror("execve");
	child_cleanup(path);
	free_split(env_matrix);
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
	int	original_stdin;
	int	original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (handle_redirections(token) == -1)
	{
		info->exit_code = 1;
		dup2(original_stdin, STDIN_FILENO);
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdin);
		close(original_stdout);
		return ;
	}
	info->exit_code = exec_bultin(token, info);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}

/*Executa os comandos, faz um fork no processo pai
e se for bem sucessedido ele chama o child_process e 
guarda o status de saída, guandando na variavel exit_code*/
void	exec_cmd(t_token *token, t_info *info)
{
	pid_t	pid;
	int		status;

	/*tenho que fazer uma verificação aqui pra nao dar bosta
	tipo se for só cd ou export, etc*/
	if (is_parent_builtin(token) & !token->next
		&& !token->prev && is_parent_builtin(token))
	{
		exec_parent_builtin(token, info);
		return ;
	}
	pid = fork();
	g_sig = (int)pid;
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
