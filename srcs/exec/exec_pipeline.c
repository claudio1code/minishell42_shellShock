/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 19:04:49 by claudio           #+#    #+#             */
/*   Updated: 2026/01/05 15:49:35 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* aqui o processo filho dos nós q vao ser do lado esquerdo da árvore,
fecho o fd de leitura, pq nao vou precisar dele agr
redireciono STDOUT para o pipe de escrita
e logo após fecho o original de escrita tbm, 
chamo o exec_tree que vai
verificar se é um pipe ou um cmd*/
static void	child_one(t_logic *node, t_info *info, int fd[2])
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	exec_tree(node->left, info);
	exit(EXIT_FAILURE);
}

/*faço a mesma coisa só que para o lado diretiro da árvore, mas 
dessa vez fechando o fd de escrita, ja que ele não vai ser usado*/
static void	child_two(t_logic *node, t_info *info, int fd[2])
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	exec_tree(node->right, info);
	exit(EXIT_FAILURE);
}

/*função auxiliar para fechar os fd, só pq estava dando 26 linhas*/
static void	close_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

/*O processo pai cria os processos filhos, os dois correm paralelamente
o pai fecha os fds, porque se por exemplo o fd[1] de escrita não fechasse
o two process ficaria esperando para sempre
e no final guardo o código de saída*/
static void	parent_process(t_logic *node, t_info *info, int fd[2])
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;

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
	close_fd(fd);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		info->exit_code = WEXITSTATUS(status);
}

/*Arvore é executada, então se for um pipe eu chamo a função do
processo pai, que vai cuidar da cominicação dos fd, mas caso seja 
um comando chama a função exec cmd*/
void	exec_tree(t_logic *node, t_info *info)
{
	int		fd[2];

	if (!node)
		return ;
	if (node->operator && !ft_strncmp(node->operator, "|", 2))
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		parent_process(node, info, fd);
	}
	else
		exec_cmd(node->cmd, info);
}
