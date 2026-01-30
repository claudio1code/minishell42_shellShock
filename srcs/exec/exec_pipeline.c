/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 19:04:49 by claudio           #+#    #+#             */
/*   Updated: 2026/01/30 14:50:49 by clados-s         ###   ########.fr       */
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

/*função auxiliar e espera todos os filhos*/
static void	wait_children(t_info *info)
{
	while (waitpid(-1, &info->exit_code, 0) > 0)
		continue;
	if (WIFEXITED(info->exit_code))
		info->exit_code = WEXITSTATUS(info->exit_code);
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
	exec_cmd(token, info);
	exit(info->exit_code);
}

/*executa o pipeline de comandos, verifica se há um próximo
token e cria um pipe se necessário*/
void	exec_pipeline(t_token *token, t_info *info)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	if (error(token))
		return ;
	if (token && !token->next && !token->prev && is_parent_builtin(token))
	{
		exec_cmd(token, info);
		return ;
	}
	while (token)
	{
		if (token->next && pipe(fd) == -1)
			return (perror("pipe"));
		pid = fork();
		if (pid == -1)
			return (perror ("fork"));
		if (pid == 0)
			child_process(token, info, fd, prev_fd);
		if (token->next)
			parent_process(fd, &prev_fd);
		else if (prev_fd != -1)
			close(prev_fd);
		token = token->next;
	}
	wait_children(info);
}
