#include "../../includes/minishell.h"
#include <fcntl.h>
#include <unistd.h>

void	init_info(t_info *info, char **envp)
{
	info->env = envp;
	info->exit_code = 0;
	info->l = NULL;
	info->str = NULL;
	info->tree = NULL;
	info->list = NULL;
}

t_token	*creat_mock_token(char **args, char **redir)
{
	static t_token	token;

	token.cmd = NULL;
	token.param = args;
	token.rdc = redir;
	return (&token);
}

void	print_banner(char *title)
{
	printf("\n\033[1;33m=== TESTE: %s ===\033[0m\n", title);
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
		printf("\033[0;32m[PASS]\033[0m: Código de saída é %d como esperado.\n", expected_exit_code);
	else
		printf("\033[0;31m[FAIL]\033[0m: Esperado %d, mas foi %d.\n", expected_exit_code, info->exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	(void)argc;
	(void)argv;

	init_info(&info, envp);

	printf("\033[1;36mIniciando Bateria de Testes do Executor...\033[0m\n");

	// Comente/Descomente para rodar testes específicos
	// test_ls(&info);
	// test_redirect_out(&info);
	test_redirect_append(&info);
	test_redirect_in(&info);
	test_cmd_not_found(&info);

	return (0);
}
