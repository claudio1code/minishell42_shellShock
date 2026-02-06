/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 09:22:01 by cacesar-          #+#    #+#             */
/*   Updated: 2026/02/06 19:33:02 by clados-s         ###   ########.fr       */
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
	if (t < 0)
	{
		signal(SIGINT, signaler);
		signal(SIGQUIT, SIG_IGN);
		signal(EOF, SIG_IGN);
		return ;
	}
	// printf("pid: %d\n", getpid());
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
	if (ft_strchr("?#$ ", i->l[(*c)]) && i->l[*c])
		(*c)++;
	else
		while (ft_isalnum(i->l[*c]))
			(*c)++;
	if (*c > 0 && i->l[*c] == '\"' && i->l[(*c) - 1] == '$')
		var = ft_strdup("\"");
	else
		var = ft_substr(i->l, *b, *c - *b);
	if (*var)
		*b = --(*c);
	return (var);
}

t_info	*data_init(int argc)
{
	t_info			*data;
	struct dirent	*tmp;
	DIR				*dtmp;

	dtmp = opendir("/proc/self/task/");
	tmp = readdir(dtmp);
	while (tmp->d_name[0] == '.')
		tmp = readdir(dtmp);
	data = ft_calloc(sizeof(t_info), 1);
	data->exit_code = 0;
	data->argc = argc;
	data->error = 0;
	data->bonus = 0;
	data->in_backup = -1;
	data->out_backup = -1;
	data->pid = ft_strdup(tmp->d_name);
	closedir(dtmp);
	return (data);
}

int	main(int argc, char**argv, char**envp)
{
	t_info	*data;
	int		c;

	data = data_init(argc - 1);
	init_env_table(data, envp);
	signaler(ft_atoi(data->pid) * -1);
	while (argv && envp && argc)
	{
		c = -1;
		if (data->exit_code != g_sig)
			g_sig = 0;
		data->l = readline(GREEN "[SHELLSHOCK]: " RESET);
		if (g_sig)
			data->exit_code = g_sig;
		if (!data->l)
			break ;
		lexer(data, &data->count, &data->begin);
		while (data->exec[++c])
			exec_pipeline(data->exec[c], data);
		data->exec = clean_token(data->exec);
	}
	ft_putendl_fd("exit", 1);
	clean_shell(data);
	return (0);
}
