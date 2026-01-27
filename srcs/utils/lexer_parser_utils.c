/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 09:22:01 by cacesar-          #+#    #+#             */
/*   Updated: 2026/01/27 09:37:46 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parse.h"

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
	write(1, "\n", 1);
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

//A função env_maker cria um cópia do environment do shell
//para utilização do minishell
//*i = struct data;
//**envp = parametro envp recebido da main;

void	env_maker(t_info*i, char**envp)
{
	int	c1;

	c1 = -1;
	i->count = 0;
	while (envp[++c1])
		;
	i->env = ft_calloc(c1 + 1, 8);
	c1 = -1;
	while (envp[++c1])
		i->env[c1] = ft_strdup(envp[c1]);
	i->env[c1] = 0;
	i->exit_code = 0;
	i->error = 0;
}

int	main(int argc, char**argv, char**envp)
{
	t_info				*data;
	t_token				**teste;
	int					c1;
	int					c2;

	data = malloc(sizeof(t_info));
	env_maker(data, envp);
	signaler(-42);
	while (argv && envp && argc)
	{
		data->l = readline("Shellshock: ");
		if (!data->l)
			continue ;
		lexer(data, &data->count, &data->begin);
		//teste
		//VVVVV
		c1 = 0;
		teste = data->exec;
		ft_putendl_fd("", 1);
		ft_putendl_fd("LISTA LINKADA PARA EXECUTAR", 1);
		ft_putendl_fd("|||||||||||||||||||||||||||", 1);
		ft_putendl_fd("VVVVVVVVVVVVVVVVVVVVVVVVVVV", 1);
		ft_putendl_fd("", 1);
		while (teste[c1])
		{
			if (error(teste[c1]))
			{
				ft_putendl_fd("", 1);
				ft_putendl_fd("=================", 1);
				ft_putendl_fd("", 1);
				c1++;
				continue ;
			}
			c2 = 0;
			if (teste[c1]->rdc && teste[c1]->rdc[0])
			{	
				ft_putendl_fd("---rdc---", 1);
				while (teste[c1]->rdc[c2])
				{
					ft_putstr_fd("    ", 1);
					ft_putendl_fd(teste[c1]->rdc[c2++], 1);
				}
				ft_putendl_fd("---rdc---", 1);
			}
			c2 = 0;
			ft_putendl_fd("", 1);
			ft_putendl_fd("", 1);
			if (teste[c1]->cmd && teste[c1]->cmd[0])
			{
				ft_putendl_fd("----cmd----", 1);
				ft_putstr_fd("    ", 1);
				ft_putendl_fd(teste[c1]->cmd, 1);
				ft_putendl_fd("----cmd----", 1);
			}
			ft_putendl_fd("", 1);
			ft_putendl_fd("", 1);
			if (teste[c1]->param && teste[c1]->param[0])
			{
				ft_putendl_fd("----param----", 1);
				while (teste[c1]->param[c2])
				{
					ft_putstr_fd("    ", 1);
					ft_putendl_fd(teste[c1]->param[c2++], 1);
				}
				ft_putendl_fd("----param----", 1);
			}
			ft_putendl_fd("", 1);
			ft_putendl_fd("", 1);
			if (teste[c1]->next)
			{
				ft_putendl_fd("        ||    ||", 1);
				ft_putendl_fd("        ||PIPE||", 1);
				ft_putendl_fd("        ||    ||", 1);
				teste[c1] = teste[c1]->next;
				continue ;
			}
			c1++;
			ft_putendl_fd("", 1);
			ft_putendl_fd("=================", 1);
			ft_putendl_fd("", 1);
		}
		//^^^^^^^
		//teste
	}
	return (0);
}
