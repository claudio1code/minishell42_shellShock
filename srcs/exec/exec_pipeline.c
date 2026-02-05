/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 19:04:49 by claudio           #+#    #+#             */
/*   Updated: 2026/02/05 13:47:50 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Processo pai do pipeline, fecho o fd de escrita e vejo 
se o tem um pipe anterior caso exista, fecho o fd anterior
e atualizo o prev_fd */
static void	parent_process(int fd[2], int *prev_fd)
{
	close(fd[1]);
	if (*prev_fd != -1)
		close(*prev_fd);
	*prev_fd = fd[0];
}

/* mudança na lógica para lista linkada
verifico se exite um pipe anterior, se sim, ele redireciona
para o stdin e fecha o prev, se houver um próximo, ele fecha
pra leitura e redireciona o fd de escrito para o stdout, chama
o exec_cmd que vai tratar os redirects e executar o comando, tbm
guarda o status de saída na variavel exit_code 
*/
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
	while (waitpid(-1, &info->exit_code, 0) > 0)
		continue ;
	if (WIFEXITED(info->exit_code))
		info->exit_code = WEXITSTATUS(info->exit_code);
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
	/*o PAi (shell) ignora os sinais enquanto o pipeline corre, antes o
	signaler estava duplicando o prompt por estar correndo no pai*/
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (token && !token->next && !token->prev && is_parent_builtin(token))
		exec_cmd(token, info);
	else
		loop_pipeline(token, info);
	/*restaura o sinal e o pai volta ouvir sinais da readline*/
	signal(SIGINT, signaler);
	cleanup_heredocs(token);
}
