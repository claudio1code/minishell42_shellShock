#include "../../includes/minishell.h"

void	free_info_env(t_info *info)
{
	int	i;

	if (!info || !info->env)
		return ;
	i = 0;
	while (info->env[i])
	{
		free(info->env[i]);
		info->env[i] = NULL; // Defensive programming
		i++;
	}
	free(info->env);
	info->env = NULL; // Defensive programming
}

void	init_info(t_info *info, char **envp)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (envp[count])
		count++;
	info->env = ft_calloc(sizeof(char *), count + 1);
	if (!info->env)
	{
		// Handle allocation error
		perror("ft_calloc failed for info->env");
		exit(EXIT_FAILURE);
	}
	while (i < count)
	{
		info->env[i] = ft_strdup(envp[i]);
		if (!info->env[i])
		{
			// Handle allocation error, free previously allocated strings
			while (i > 0)
			{
				i--;
				free(info->env[i]);
			}
			free(info->env);
			perror("ft_strdup failed for envp element");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	info->env[i] = NULL; // Null-terminate the array

	info->exit_code = 0;
	info->l = NULL;
	info->str = NULL;
	info->tree = NULL;
	info->list = NULL;
}

t_token	*creat_mock_token(char **args, char **redir)
{
	t_token	*t = malloc(sizeof(t_token));
	t->cmd = NULL;

	t->param = args;
	t->rdc = redir;
	return (t);
}

t_logic	*new_node(char *operator, t_logic *left, t_logic *right, t_token *cmd)
{
	t_logic	*node = malloc(sizeof(t_logic));
	node->operator = operator;
	node->left = left;
	node->right = right;
	node->cmd = cmd;
	return (node);
}

void	print_banner(char *title)
{
	printf("\n\033[1;33m=== TESTE: %s ===\033[0m\n", title);
}

void	test_pipeline_ls_grep(t_info *info)
{
	int	saved_stdout = dup(STDOUT_FILENO);
	int	success = 0;
	int	fd = open("grep_test_result.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	int	bytes_read;
	char	buffer[5000];

	print_banner("ls - la | grep makefile (Pipeline Simples)");

	if (fd == -1)
	{
		perror("open temp file");
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);

	// 1. Token Esquerdo: ls -la
	char	*args_ls[] = {"ls", "-la", NULL};
	char	*args_grep[] = {"grep", "make", NULL};

	t_token	*tok_ls = creat_mock_token(args_ls, NULL);
	t_logic	*node_ls = new_node(NULL, NULL, NULL, tok_ls);

	//2. Token Direito: grep make
	t_token *tok_grep = creat_mock_token(args_grep, NULL);
	t_logic	*node_grep = new_node(NULL, NULL, NULL, tok_grep);

	//3. Nó Raiz (PIPE)
	t_logic	*root = new_node("|", node_ls, node_grep, NULL);
	exec_tree(root, info);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	fd = open("grep_test_result.txt", O_RDONLY);
	ft_bzero(buffer, 100);
	bytes_read = read(fd, buffer, 99);
	close(fd);

	if (bytes_read > 0)
	{
		if (ft_strnstr(buffer, "makefile", 4096))
			success = 1;
	}
	if (success)
		printf("\033[0;32m[SUCCESS]\033[0m: Encontrou 'makefile' no output.\n");
	else
		printf("\033[0;31m[FAIL]\033[0m: Output incorreto. Recebido: \n%s\n", buffer);
	system("rm -f grep_test_result.txt");
	free(tok_ls); free(node_ls);
	free(tok_grep); free(node_grep);
	free(root);
}

void	test_pipeline_complex(t_info *info)
{
	int	saved_stdout = dup(STDOUT_FILENO);
	int	success = 0;
	int fd;
	char	buffer[100];
	int	bytes_read;


	print_banner("ls | grep c | wc -l (Pipeline Duplo)");
	fd = open("pipeline_result.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open temp file");
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);

	// Comando 1: ls
	char *a1[] = {"ls", NULL};
	t_logic *n1 = new_node(NULL, NULL, NULL, creat_mock_token(a1, NULL));

	// Comando 2: grep c
	char *a2[] = {"grep", "c", NULL};
	t_logic *n2 = new_node(NULL, NULL, NULL, creat_mock_token(a2, NULL));

	// Pipe 1 (Esquerda): ls | grep c
	t_logic *pipe1 = new_node("|", n1, n2, NULL);

	// Comando 3: wc -l
	char *a3[] = {"wc", "-l", NULL};
	t_logic *n3 = new_node(NULL, NULL, NULL, creat_mock_token(a3, NULL));

	// Pipe Raiz: (Pipe1) | wc -l
	t_logic *root = new_node("|", pipe1, n3, NULL);

	exec_tree(root, info);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);

	// 5. Verificar o conteúdo do arquivo
	fd = open("pipeline_result.txt", O_RDONLY);
	ft_bzero(buffer, 100);
	bytes_read = read(fd, buffer, 99);
	close(fd);

	if (bytes_read > 0)
	{
		int i = 0;
		while (buffer[i] == ' ' || buffer[i] == '\t') // Pular espaços
			i++;
		if (ft_isdigit(buffer[i]))
		{
			success = 1;
			printf("\033[0;32m[PASS]\033[0m: Output capturado corretamente: %s\n", buffer);
		}
		else
			printf("\033[0;31m[FAIL]\033[0m: Esperava um número, recebeu: %s\n", buffer);
	}
	else
		printf("\033[0;31m[FAIL]\033[0m: Output vazio ou erro na leitura.\n");
	system("rm -f pipeline_result.txt");
}

void	test_redirect_out(t_info *info)
{
	char	*args[] = {"echo", "Teste de Saída", NULL};
	char	*redir[] = {">", "out_test.txt", NULL};
	char	*expected = "Teste de Saída\n";
	int		fd;
	char	buffer[256];
	ssize_t	bytes_read;
	int		success = 0;


	print_banner("echo 'Teste de Saída' > out_test.txt (Redirect >)	");
	exec_cmd(creat_mock_token(args, redir), info);
	fd = open("out_test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("\033[0;31m[FAIL]\033[0m;O arquivo 'output.txt' não foi criado.\n");
		return ;
	}
	ft_bzero(buffer, 100);
	bytes_read = read(fd, buffer, 99);
	close(fd);
	if (bytes_read > 0)
	{
		if (!strcmp(buffer, expected))
			success = 1;
	}
	if (success)
		printf("\033[0;32m[PASS]\033[0m: Conteúdo verificado com sucesso.\n\nEsperado: %s\nRecebido: %s", expected, buffer);
	else
		printf("\033[0;31m[FAIL]\033[0m: Conteúdo incorreto.\nEsperado: %s\nRecebido: %s\n", expected, buffer);

	system("rm -f out_test.txt");
	
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
	size_t	pos = 0;
	int		success = 1;

	print_banner("Append >> (Criar arquivo e adicionar linhas)");
	exec_cmd(creat_mock_token(args1, redir), info);
	exec_cmd(creat_mock_token(args2, redir2), info);

	fd = open("append_test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("\033[0;31m[FAIL]\033[0m: Não foi possível abrir 'append_test.txt'.\n");
		success = 0;
	}
	else
	{
		while ((n = read(fd, buffer + pos, sizeof(buffer) - 1 - pos)) > 0)
			pos += n;
		close(fd);
		if (n < 0)
			success = 0;
		else
		{
			buffer[pos] = '\0';
			if (strcmp(buffer, "Linha 1\nLinha 2\n") != 0)
				success = 0;
		}
	}
	if (success)
		printf("\033[0;32m[PASS]\033[0m: Conteúdo de 'append_test.txt' correto.\n");
	else
		printf("\033[0;31m[FAIL]\033[0m: Conteúdo de 'append_test.txt' incorreto ou número de linhas errado.\n");
	system("rm -f append_test.txt");
}

void	test_redirect_in(t_info *info)
{
	char	*args[] = {"cat", NULL};
	char	*redir[] = {"<", "input.txt", ">", "output.txt", NULL};
	char	*input_content = "1 2 testando ...\n";
	int		fd;
	char	buffer[256] = {0};
	ssize_t	n;
	int		success = 1;

	print_banner("cat < input.txt > output.txt (Input/Output Redirect)");
	system("echo '1 2 testando ...' > input.txt");
	exec_cmd(creat_mock_token(args, redir), info);

	fd = open("output.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("\033[0;31m[FAIL]\033[0m: Não foi possível abrir 'output.txt' para verificação.\n");
		success = 0;
	}
	else
	{
		n = read(fd, buffer, sizeof(buffer) - 1);
		close(fd);
		if (n < 0)
			success = 0;
		else
		{
			buffer[n] = '\0';
			if (strcmp(buffer, input_content) != 0)
				success = 0;
		}
	}

	if (success)
		printf("\033[0;32m[PASS]\033[0m: O output do 'cat' foi redirecionado corretamente.\n");
	else
		printf("\033[0;31m[FAIL]\033[0m: O conteúdo do arquivo de saída não corresponde ao esperado.\n");

	system("rm -f input.txt output.txt");
}

void	test_cmd_not_found(t_info *info)
{
	char	*args[] = {"projetinho_felas", NULL};
	int		expected_exit_code = 127;

	print_banner("Comand not found (saída esperada 127)");
	t_token *token= creat_mock_token(args, NULL);
	exec_cmd(token, info);
	if (info->exit_code == expected_exit_code)
		printf("\033[0;32m\n[PASS]\033[0m: Código de saída é %d como esperado.\n\n", expected_exit_code);
	else
		printf("\033[0;31m[FAIL]\033[0m: Esperado %d, mas foi %d.\n\n", expected_exit_code, info->exit_code);
}

void test_echo(t_info *info)
{
	char	*args[] = {"echo", "-n", "Eae", "Felas", NULL};
	t_token	*token = creat_mock_token(args, NULL);
	int		saved_stdout = dup(STDOUT_FILENO);
	int		fd;
	char	buffer[256];
	ssize_t	bytes_read;

	print_banner("echo -n 'Eae Felas' (Echo sem nova linha)");

	fd = open("echo_test_result.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open temp file");
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);

	exec_bultin(token, info);

	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);

	fd = open("echo_test_result.txt", O_RDONLY);
	ft_bzero(buffer, 256);
	bytes_read = read(fd, buffer, 255);
	close(fd);

	if (bytes_read > 0 && !strcmp(buffer, "Eae Felas"))
		printf("\033[0;32m[PASS]\033[0m:'echo' output correto sem nova linha.\n");
	else
		printf("\033[0;31m[FAIL]\033[0m: 'echo' output incorreto. Recebido: '%s'\n", buffer);

	system("rm -f echo_test_result.txt");
}

void	test_cd(t_info *info)
{
	char	*args[] = {"cd", "~", NULL};
	int		success = 0;
	char	*cwd;
	t_token	*token = creat_mock_token(args, NULL);

	print_banner("cd ~ (Change Directory)");

	exec_bultin(token, info);
	cwd = getcwd(NULL, 0);
	if (cwd && !strcmp(cwd, "~"))
		success = 1;

	if (success)
		printf("\033[0;32m[PASS]\033[0m: Diretório alterado para '~'.\n");
	else
		printf("\033[0;31m[FAIL]\033[0m: Falha ao alterar diretório. Diretório atual: '%s'\n", cwd ? cwd : "NULL");

	free(cwd);
}

void	test_pwd(t_info *info)
{
	char	*args[] = {"pwd", NULL};
	t_token	*token = creat_mock_token(args, NULL);
	char	expected[1024];
	int		len;

	print_banner("pwd (Print Working Directory)");
	getcwd(expected, sizeof(expected));
	exec_bultin(token, info);
	len = ft_strlen(expected);
	printf("\n\033[0;32m[PASS]\033[0m: pwd executado. Verifique se o diretório atual é: %s\n", expected);
}


int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	// t_token	token;
	(void)argc;
	(void)argv;

	init_info(&info, envp);

	printf("\033[1;36mIniciando Bateria de Testes do Executor...\033[0m\n");

	test_pipeline_ls_grep(&info);
	test_pipeline_complex(&info);
	test_redirect_out(&info);
	test_redirect_append(&info);
	test_redirect_in(&info);
	test_cmd_not_found(&info);
	test_echo(&info);
	test_cd(&info);
	test_pwd(&info);

	free_info_env(&info);

	return (0);
}
