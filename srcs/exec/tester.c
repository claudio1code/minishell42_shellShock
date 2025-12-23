#include "../../includes/minishell.h"

void	init_info(t_info *info, char **envp)
{
	info->env = envp;
	info->exit_code = 0;
	info->l = NULL;
	info->str = NULL;
	info->tree = NULL;
	info->list = NULL;
}

t_token	*creat_mock_token(char **args, char redir)
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

	print_banner("Append >> (Criar arquivo e adicionar linhas)");
	exec_cmd(creat_mock_token(args1, redir), info);
	exec_cmd(creat_mock_token(args2, redir2), info);
	printf("\033[0;32mVerificando se tem 2 linhas:\033[0m\n");
	system("cat append_test.txt");
	system("rm append_test.txt");
}

void	test_redirect_in(t_info *info)
{
	char	*args[] = {"cat", NULL};
	char	*redir[] = {"<", "input.txt", NULL};

	print_banner("cat < input.txt (Redirect Input)");
	system("echo '1 2 testando ...' > input.txt");
	exec_cmd(creat_mock_token(args, redir), info);
	system("rm input.txt");
}

void	test_cmd_not_found(t_info *info)
{
	char	*args[] = {"projetinho_felas", NULL};

	print_banner("Comand not found (saída esperada 127)");
	t_token *token= creat_mock_token(args, NULL);
	exec_cmd(token, info);
	printf("'exid_code' guardado na struct: %d\n", info->exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	(void)argc;
	(void)argv;

	init_info_mock(&info, envp);

	printf("\033[1;36mIniciando Bateria de Testes do Executor...\033[0m\n");

	// Comente/Descomente para rodar testes específicos
	test_ls(&info);
	test_redirect_out(&info);
	test_redirect_append(&info);
	test_redirect_in(&info);
	test_cmd_not_found(&info);

	return (0);
}
