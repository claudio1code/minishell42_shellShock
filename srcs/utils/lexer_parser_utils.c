/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 09:22:01 by cacesar-          #+#    #+#             */
/*   Updated: 2026/01/29 15:37:17 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_sig = 0;
//A função ft_chr_num checa quantos lista linkadas
//para execução serão necessarias;
//*str = retorno da readline
//*i = struct data;

int	ft_chr_num(char*str, t_info*i)
{
	int	c;
	int	result;

	c = -1;
	result = 1;
	while (str[++c])
		if (str[c] == '\n')
			result++;
	i->c3 = result;
	return (result);
}

void	signaler(int t)
{
	if (t == -42)
	{
		signal(SIGINT, signaler);
		signal(SIGQUIT, SIG_IGN);
		signal(EOF, SIG_IGN);
	}
	g_sig = 130;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

//A função var_maker cria uma string com a variavel passada para expansão
//para facilitar a procura na matrix env;
//*i = struct data;
//*c = countador usado para percorrer o retorno da readline;
//*b = countador usada para marcar o começo do parametro achado no retorno da
//readline, utilizado na ft_substr;
char	*var_maker(t_info*i, unsigned int *c, unsigned int *b)
{
	char	*var;

	*b = *c;
	while (!ft_strchr("&|<>\n\'\" ", i->l[*c]))
		(*c)++;
	var = ft_substr(i->l, *b, *c - *b);
	if (*var)
		*b = --(*c);
	return (var);
}

int	main(int argc, char**argv, char**envp)
{
	t_info	*data;
	int		c;

	data = malloc(sizeof(t_info));
	init_env_table(data, envp);
	signaler(-42);
	while (argv && envp && argc)
	{
		c = -1;
		if (data->exit_code != g_sig)
			g_sig = 0;
		data->l = readline("Shellshock: ");
		if (g_sig)
			data->exit_code = g_sig;
		if (!data->l)
			break ;
		lexer(data, &data->count, &data->begin);
		while (data->exec[++c])
			exec_pipeline(data->exec[c], data);
	}
	ft_putendl_fd("exit", 1);
	clean_shell(data);
	return (0);
}
