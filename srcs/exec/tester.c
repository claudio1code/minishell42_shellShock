#include "../../includes/minishell.h"
#include <fcntl.h>
#include <sys/wait.h>

/* --- Helpers de Limpeza --- */

void	free_info_env(t_info *info)
{
	int			i;
	t_env_node	*tmp;
	t_env_node	*next;

	if (!info || !info->env)
		return ;
	i = 0;
	while (i < TABLE_SIZE)
	{
		tmp = info->env->buckets[i];
		while (tmp)
		{
			next = tmp->next;
			free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			tmp = next;
		}
		i++;
	}
	free(info->env);
}

void	init_info(t_info *info, char **envp)
{
	// Usa a tua função nova para criar a Hash Table
	init_env_table(info, envp);
	
	info->exit_code = 0;
	info->l = NULL;
	info->str = NULL;
	// info->list = NULL; (Se usares listas noutro sitio)
}

/* Cria um token limpo e seguro */
t_token	*creat_mock_token(char **args, char **redir)
{
	t_token	*t;

	t = ft_calloc(1, sizeof(t_token)); // Calloc zera next, prev, infile, etc.
	if (!t)
		return (NULL);
	t->param = args;
	t->rdc = redir;
	
	// Previne que o executor tente fechar FDs invalidos se nao forem usados
	t->in = 0; 
	t->out = 1;
	return (t);
}

void	print_banner(char *title)
{
	printf("\n\033[1;33m=== TESTE: %s ===\033[0m\n", title);
}

/* --- TESTES DE REDIRECTION --- */

void	test_redirect_out(t_info *info)
{
	char	*args[] = {"echo", "Teste de Saida", NULL};
	char	*redir[] = {">", "out_test.txt", NULL};
	char	*expected = "Teste de Saida\n";
	int		fd;
	char	buffer[256];
	ssize_t	bytes_read;

	print_banner("Redirect Output (>)");
	exec_cmd(creat_mock_token(args, redir), info);
	
	fd = open("out_test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("\033[0;31m[FAIL]\033[0m: Arquivo nao criado.\n");
		return ;
	}
	ft_bzero(buffer, 256);
	bytes_read = read(fd, buffer, 255);
	close(fd);
	if (bytes_read > 0 && !strcmp(buffer, expected))
		printf("\033[0;32m[PASS]\033[0m: Conteudo correto.\n");
	else
		printf("\033[0;31m[FAIL]\033[0m: Conteudo incorreto.\n");
	unlink("out_test.txt");
}

void	test_redirect_append(t_info *info)
{
	char	*args1[] = {"echo", "Linha 1", NULL};
	char	*args2[] = {"echo", "Linha 2", NULL};
	char	*redir[] = {">", "append_test.txt", NULL};
	char	*redir2[] = {">>", "append_test.txt", NULL};
	int		fd;
	char	buffer[256];
	ssize_t	n;

	print_banner("Redirect Append (>>)");
	exec_cmd(creat_mock_token(args1, redir), info);
	exec_cmd(creat_mock_token(args2, redir2), info);

	fd = open("append_test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("\033[0;31m[FAIL]\033[0m: Arquivo nao aberto.\n");
		return ;
	}
	n = read(fd, buffer, 255);
	close(fd);
	buffer[n] = '\0';

	if (strcmp(buffer, "Linha 1\nLinha 2\n") == 0)
		printf("\033[0;32m[PASS]\033[0m: Append funcionou.\n");
	else
		printf("\033[0;31m[FAIL]\033[0m: Conteudo errado.\n");
	unlink("append_test.txt");
}

void	test_redirect_in(t_info *info)
{
	char	*args[] = {"cat", NULL};
	char	*redir[] = {"<", "input.txt", ">", "output.txt", NULL};
	char	*content = "Testando input redirect\n";
	char	buffer[256] = {0};
	int		fd;

	print_banner("Redirect Input (<)");
	
	// Cria arquivo de entrada
	fd = open("input.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, content, ft_strlen(content));
	close(fd);

	exec_cmd(creat_mock_token(args, redir), info);

	fd = open("output.txt", O_RDONLY);
	read(fd, buffer, 255);
	close(fd);

	if (strcmp(buffer, content) == 0)
		printf("\033[0;32m[PASS]\033[0m: Input redirecionado.\n");
	else
		printf("\033[0;31m[FAIL]\033[0m: Falha no redirect.\n");
	
	unlink("input.txt");
	unlink("output.txt");
}

/* --- TESTES DE BUILTINS --- */

void	test_export_unset(t_info *info)
{
	char	*args_exp[] = {"export", "TESTE_VAR=funciona", NULL};
	char	*args_uns[] = {"unset", "TESTE_VAR", NULL};
	char	*val;

	print_banner("Export & Unset");

	// 1. Testar Export
	exec_bultin(creat_mock_token(args_exp, NULL), info);
	val = get_env_val(info->env, "TESTE_VAR");
	if (val && !strcmp(val, "funciona"))
		printf("\033[0;32m[PASS]\033[0m: Variavel exportada.\n");
	else
		printf("\033[0;31m[FAIL]\033[0m: Variavel nao encontrada apos export.\n");

	// 2. Testar Unset
	exec_bultin(creat_mock_token(args_uns, NULL), info);
	val = get_env_val(info->env, "TESTE_VAR");
	if (!val)
		printf("\033[0;32m[PASS]\033[0m: Variavel removida com unset.\n");
	else
		printf("\033[0;31m[FAIL]\033[0m: Variavel ainda existe apos unset.\n");
}

void	test_cd_pwd(t_info *info)
{
	char	*args_cd[] = {"cd", "..", NULL};
	char	*args_pwd[] = {"pwd", NULL};
	char	cwd_before[1024];
	char	cwd_after[1024];

	print_banner("CD & PWD");
	
	getcwd(cwd_before, 1024);
	
	// Executa CD ..
	exec_bultin(creat_mock_token(args_cd, NULL), info);
	
	getcwd(cwd_after, 1024);
	
	if (strcmp(cwd_before, cwd_after) != 0)
		printf("\033[0;32m[PASS]\033[0m: Diretorio mudou de %s para %s\n", cwd_before, cwd_after);
	else
		printf("\033[0;31m[FAIL]\033[0m: Diretorio nao mudou.\n");

	// Executa PWD (visual apenas)
	printf("Saida do PWD: ");
	fflush(stdout);
	exec_bultin(creat_mock_token(args_pwd, NULL), info);
	
	// Volta ao original para nao quebrar outros testes
	chdir(cwd_before);
}

/* --- TESTE DE EXECUÇÃO --- */

void	test_cmd_not_found(t_info *info)
{
	char	*args[] = {"comando_inexistente_xyz", NULL};
	int		pid;
	int		status;

	print_banner("Command Not Found (127)");
	
	// Fazemos fork manual aqui pois o exec_cmd pode fazer exit(127) direto
	// e matar o tester se nao for num filho.
	pid = fork();
	if (pid == 0)
	{
		exec_cmd(creat_mock_token(args, NULL), info);
		exit(0); // Backup exit
	}
	waitpid(pid, &status, 0);
	
	if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
		printf("\033[0;32m[PASS]\033[0m: Exit code 127 recebido.\n");
	else
		printf("\033[0;31m[FAIL]\033[0m: Exit code incorreto: %d\n", WEXITSTATUS(status));
}

void	test_pipeline_mock(t_info *info)
{
	char	*ls_args[] = {"ls", NULL};
	char	*wc_args[] = {"wc", "-l", NULL};
	t_token	*t1;
	t_token	*t2;

	print_banner("Pipeline Mock: ls | wc -l");
	
	t1 = creat_mock_token(ls_args, NULL);
	t2 = creat_mock_token(wc_args, NULL);

	// Linkar os tokens manualmente
	t1->next = t2;
	t2->prev = t1;

	printf("Executando pipeline... (Verifique a saida visual)\n");
	exec_pipeline(t1, info);
	
	// Limpeza manual dos tokens mockados
	free(t1);
	free(t2);
}

/* --- MAIN --- */

int	main(int argc, char **argv, char **envp)
{
	t_info	info;

	(void)argc;
	(void)argv;

	init_info(&info, envp);

	printf("\033[1;36mIniciando Bateria de Testes do Executor (Hash Table Version)...\033[0m\n");

	// Testes de Redirect
	test_redirect_out(&info);
	test_redirect_append(&info);
	test_redirect_in(&info);

	// Testes de Builtins
	test_export_unset(&info);
	test_cd_pwd(&info);

	// Testes de Execução e Erros
	test_cmd_not_found(&info);
	
	// Teste de Pipeline
	test_pipeline_mock(&info);

	printf("\n\033[1;36mLimpeza e Fim dos Testes.\033[0m\n");
	free_info_env(&info);

	return (0);
}