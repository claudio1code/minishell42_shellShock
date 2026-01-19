/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftlurker <ftlurker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:01:06 by cacesar-          #+#    #+#             */
/*   Updated: 2026/01/19 02:38:41 by ftlurker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

//A função var_maker cria uma string com a variavel passada para expansão
//para facilitar a procura na matrix env;
//*i = struct data;
//*c = countador usado para percorrer o retorno da readline;
//*b = countador usada para marcar o começo do parametro achado no retorno da readline, utilizado na ft_substr;
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
//A função expansion expandi variaveis passadas e contatena elas ao
//restante do parametro se existir;
//*i = struct data;
//*p = lista linkada onde o retorno da readline sera quebrado em parametros para a execução;
//*c = countador usado para percorrer o retorno da readline;
//*b = countador usada para marcar o começo do parametro achado no retorno da readline, utilizado na ft_substr;
void	expansion(t_info*i, unsigned int *c, unsigned int *b, t_list*p)
{
	char	*var;
	int		c1;
	int		c2;

	if (*c - *b >= 1)
		p->content = ft_strjoin(p->content,
			ft_substr(i->l, *b, *c - *b - 1), 1, 1);
	var = var_maker(i, c, b);
	c1 = -1;
	while (i->env[++c1])
	{
		c2 = -1;
		while (i->env[c1][++c2] != '=')
		{
			if (i->env[c1][c2] != var[c2])
				break ;
		}
		if (i->env[c1][c2] != '=' || var[c2++])
			continue ;
		p->content = ft_strjoin(p->content, ft_substr(i->env[c1], c2,
			ft_strlen(i->env[c1] + c2)), 1, 1);
		free (var);
		break ;
	}
	*b = ++(*c);
}
//A função quotes cuida qualquer caractere q mude a leitura dos parametros,
//como '',  "" e $;
//*i = struct data;
//*p = lista linkada onde o retorno da readline sera quebrado em parametros para a execução;
//*c = countador usado para percorrer o retorno da readline;
//*b = countador usada para marcar o começo do parametro achado no retorno da readline, utilizado na ft_substr;
void	quotes(t_info*i, unsigned int *c, t_list*p, unsigned int *b)
{
	p->content = ft_strjoin(p->content,
		ft_substr(i->l, *b, *c - *b - 1), 1, 1);
	i->c2 = i->l[*c - 1];
	*b = *c;
	if (i->c2 == '\'')
		while (i->l[*c] != i->c2 && i->l[*c])
			(*c)++;
	else if (i->c2 == '\"')
		while (i->l[*c] != i->c2 && i->l[*c])
			if (i->l[(*c)++] == '$')
				expansion(i, c, b, p);
	if (i->c2 != '$')
		p->content = ft_strjoin(p->content,
			ft_substr(i->l, *b, *c - *b), 1, 1);
	else
		expansion(i, c, b, p);
	if (!((char *)p->content)[*c] && (i->c2 == '\"' || i->c2 == '\''))
		i->error = 1;
	if (i->l[*c] && (i->c2 == '\"' || i->c2 == '\''))
		(*c)++;
	*b = *c;
	p->content = p->content;
}
//A função edcase cuida de caracteres q ignoram proximidade de outros
//como &, |, <, > e \n;
//*i = struct data;
//*p = lista linkada onde o retorno da readline sera quebrado em parametros para a execução;
//*c = countador usado para percorrer o retorno da readline;
//*b = countador usada para marcar o começo do parametro achado no retorno da readline, utilizado na ft_substr;
int	edcase(t_info*i, unsigned int *c, t_list*p, unsigned int *b)
{
	i->c2 = i->l[*c];
	if (p->content && *c - *b >= 1)
		p->content = ft_strjoin(p->content,
			ft_substr(i->l, *b, *c - *b - 1), 1, 1);
	else if (*c - *b >= 1)
		p->content = ft_substr(i->l, *b, *c - *b);
	if (p->content)
		return (1);
	while (i->l[*c] == i->c2)
		(*c)++;
	p->content = ft_substr(i->l, *b, *c - *b);
	*b = *c;
	return (1);
}
//A função s_split divide a string do retorno da readline em parametros
//q serão utilizados na execução;
//*i = struct data;
//*p = lista linkada onde o retorno da readline sera quebrado em parametros para a execução;
//*c = countador usado para percorrer o retorno da readline;
// b = countador usada para marcar o começo do parametro achado no retorno da readline, utilizado na ft_substr;
t_list	*s_split(t_info*i, unsigned int *c, unsigned int b, t_list *p)
{
	int	end;

	end = 0;
	c = &i->count;
	while (i->l[*c] == ' ')
		(*c)++;
	b = *c;
	if (!i->l[*c] || i->l[*c] == '\n')
		return (p);
	p = malloc(sizeof(t_list));
	p->content = 0;
	while (i->l[*c] && i->l[*c] != ' ' && !ft_strchr("&|<>\n", i->l[*c]))
		if (ft_strchr("\'\"$", i->l[(*c)++]))
			quotes(i, c, p, &b);
	if (i->l[*c] && ft_strchr("&|<>\n", i->l[*c]))
		end = edcase(i, c, p, &b);
	if (!p->content && !end)
		p->content = ft_substr(i->l, b, *c - b);
	else if (!end)
		p->content = ft_strjoin(p->content, ft_substr(i->l, b, *c - b), 1, 1 );
	p->next = s_split(i, c, 0, 0);
	return (p);
}

// t_logic	*binary_tree(t_list*s_split)
// {
// }

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
	i->exit = 0;
	i->error = 0;
}

//A função ft_chr_num checa quantos lista linkadas para execução serão necessarias
//*str = retorno da readline
//*i = struct data;
int ft_chr_num(char*str, t_info*i)
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
//A funcção historic adiciona as saidas do readline ao historico
//*l = retorno da readline;
void historic(char	*l)
{
	int	c1;
	int	b;

	c1 = 0;
	b = 0;
	while (l[c1])
	{
		if (l[c1] == '\n')
		{
			add_history(ft_substr(l, b, c1 - b - 1));
			b = c1;
			while (l[c1] == ' ')
				c1++;
			continue ;
		}
		c1++;
	}
}

int	main(int argc, char**argv, char**envp)
{
	int		c1;
	t_info	data;

	env_maker(&data, envp);
	while (argv && envp && argc)
	{
		data.l = readline("Shellshock: ");
		if (!data.l)
			continue ;
		c1 = ft_chr_num(data.l, &data);
		historic(data.l);
		data.tree = ft_calloc(data.c3 + 1, 8);
		while (c1)
		{
			data.list = s_split(&data, 0, 0, 0);
			while(data.list)
			{
				ft_putendl_fd(data.list->content, 1);
				data.list = data.list->next;
			}
			return (0);
			// data.tree[data.c3 - c1] = binary_tree(data.list);
			// ft_lstclear(&data, ft_del);
			// c1--;
		}
	}
	return (0);
}
