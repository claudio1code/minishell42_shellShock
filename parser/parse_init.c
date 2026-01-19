/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftlurker <ftlurker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:01:06 by cacesar-          #+#    #+#             */
/*   Updated: 2026/01/19 11:33:58 by ftlurker         ###   ########.fr       */
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
	if (!i->l[*c] && (i->c2 == '\"' || i->c2 == '\''))
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
t_list	*s_split(t_info*i, unsigned int *c, unsigned int *b, t_list *p)
{
	int	end;

	end = 0;
	while (i->l[*c] == ' ')
		(*c)++;
	*b = *c;
	if (!i->l[*c] || i->l[*c] == '\n')
		return (p);
	p = malloc(sizeof(t_list));
	p->content = 0;
	while (i->l[*c] && i->l[*c] != ' ' && !ft_strchr("&|<>\n", i->l[*c]))
		if (ft_strchr("\'\"$", i->l[(*c)++]))
			quotes(i, c, p, b);
	if (i->l[*c] && ft_strchr("&|<>\n", i->l[*c]))
		end = edcase(i, c, p, b);
	if (!p->content && !end)
		p->content = ft_substr(i->l, *b, *c - *b);
	else if (!end)
		p->content = ft_strjoin(p->content,
			ft_substr(i->l, *b, *c - *b), 1, 1 );
	p->next = s_split(i, c, b, 0);
	return (p);
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
			if (c1 - b >= 2)
				add_history(ft_substr(l, b, c1 - b));
			while (l[c1] == '\n' || l[c1] == ' ')
				c1++;
			b = c1;
			continue ;
		}
		c1++;
	}
	add_history(ft_substr(l, b, c1 - b));
}
//A função cmd_fill passa o conteudo da lista linkada criada pelo lexer para a lista da execução;
//*t = ponteiro separado paro o retorno do lexer, para poder percorrer sem perder o inicio;
//*r = lista linkada q sera passa para execução;
void cmd_fill(t_list*t, t_token*r)
{
	int	c1;
	int	c2;

	c1 = 0;
	c2 = 0;
	while (t && ((char *)t->content)[0] != '|' &&
		((char *)t->content)[0] != '&')
	{
		if (((char *)t->content)[0] == '<' || ((char *)t->content)[0] == '>')
		{
			r->rdc[c1++] = ft_strdup(t->content);
			t = t->next;
			if (t)
				r->rdc[c1++] = ft_strdup(t->content);
		}
		else if (!ft_strchr("&|<>", ((char *)t->content)[0]))
		{
			if (!c2)
				r->cmd = ft_strdup(t->content);
			r->param[c2++] = ft_strdup(t->content);
		}
		if (t)
			t = t->next;
	}
}	
//A função cmd_prep me usada para pegar informações necessarias para a callocação
//das variaveis da lista linkada q sera utilizada na execução, alem servir como checagem de syntaxe;
//*t = ponteiro separado paro o retorno do lexer, para poder percorrer sem perder o inicio;
//*param = numero de parametros para execução;
//*rdc = numero de redirects;
//*i = struct data;
int	cmd_prep(t_list *t, int *param, int *rdc, t_info*i)
{
	int		len;
	char	*str;

	len = 0;
	while (t && len >= 0)
	{
		len = ft_strlen(t->content);
		str = t->content;
		if (str[0] == '<' || str[0] == '>')
			(*rdc)++;
		if ((str[0] == '<' && len > 3) || (str[0] == '>' && len > 2) ||
			(str[0] == '&' && len != 2) || (str[0] == '|' && len > 2) ||
				((str[0] == '<' || str[0] == '>') &&
					(!t->next || ((char *)t->next->content)[0] == '|')))
			i->error = 1;
		if (str[0] == '&' || (str[0] == '|' && len == 2))
			i->bonus = 1;
		if (!ft_strchr("&|<>", str[0]))
			(*param)++;
		if (str[0] == '|' || str[0] == '&')
			len = -42;
		t = t->next;
	}
	return (i->error || i->bonus);
}
//A função cmd cria o array de listas linkadas t_token para a execução;
//*t = ponteiro separado paro o retorno do lexer, para poder percorrer sem perder o inicio;
//*i = struct data;
t_token	*cmd(t_list	*t, t_info*i)
{
	t_token	*r;
	int		param;
	int		rdc;

	r = 0;
	param = 1;
	rdc = 1;
	if (!t)
		return (0);
	cmd_prep(t, &param, &rdc, i);
	param = (param > rdc) * (param - rdc);
	r = malloc(sizeof(t_token));
	r->cmd = 0;
	r->param = calloc(param + 1, 8);
	r->rdc = calloc(rdc + rdc + 1, 8);
	cmd_fill(t, r);
	while (t && ((char *)t->content)[0] != '|' &&
		((char *)t->content)[0] != '&')
		t = t->next;
	if (t && (((char *)t->content)[0] == '|' ||
		((char *)t->content)[0] == '&'))
		t = t->next;
	r->next = cmd(t, i);
	return (r);
}
//A função lexer prepara o retorno da readline para a execução;
//*i = struct data;
//*c = countador usado para percorrer o retorno da readline;
//*b = countador usada para marcar o começo do parametro achado no retorno da readline, utilizado na ft_substr;
void	lexer(t_info*i, unsigned int *c, unsigned int *b)
{
	int		c1;
	t_list	*t;
	t_token	*tmp;

	c1 = ft_chr_num(i->l, i);
	historic(i->l);
	i->exec = ft_calloc(i->c3 + 1, 8);
	*c = 0;
	*b = 0;
	while (i->l[*c])
	{
		i->list = s_split(i, c, b, 0);
		t = i->list;
		tmp = cmd(t, i);
		ft_lstclear(&i->list, ft_del);
		if (tmp)
		{
			i->exec[i->c3 - c1] = tmp;
			c1--;
		}
		if (i->l[*c])
			(*c)++;
	}
}

int	main(int argc, char**argv, char**envp)
{
	t_info				*data;
	t_token				**teste;
	int					c1;
	int					c2;

	data = malloc(sizeof(t_info));
	env_maker(data, envp);
	while (argv && envp && argc)
	{
		data->l = readline("Shellshock: ");
		if (!data->l)
			continue ;
		lexer(data, &data->count, &data->begin);
		if (data->error)
			ft_putendl_fd("Syntax Error", 1);
		if (data->bonus)
			ft_putendl_fd("I'm sorry but we are suffering from xXxSHELLSHOCKxXx", 1);
		if (data->error || data->bonus)
			continue ;
		//teste
		//VVVVV
		c1 = 0;
		teste = data->exec;
		ft_putendl_fd("", 1);
		ft_putendl_fd("LISTA LINKADA PARA EXECUTAR", 1);
		ft_putendl_fd("|||||||||||||||||||||||||||||", 1);
		ft_putendl_fd("VVVVVVVVVVVVVVVVVVVVVVVVVVVVV", 1);
		ft_putendl_fd("", 1);
		while (teste[c1])
		{
			c2 = 0;
			if (teste[c1]->rdc[0])
			{	
				ft_putendl_fd("---rdc---", 1);
				while(teste[c1]->rdc[c2])
				{
					ft_putstr_fd("    ", 1);
					ft_putendl_fd(teste[c1]->rdc[c2++], 1);
				}
				ft_putendl_fd("---rdc---", 1);
			}
			c2 = 0;
			ft_putendl_fd("", 1);
			ft_putendl_fd("", 1);
			if (teste[c1]->cmd[0])
			{
				ft_putendl_fd("----cmd----", 1);
				ft_putstr_fd("    ", 1);
				ft_putendl_fd(teste[c1]->cmd, 1);
				ft_putendl_fd("----cmd----", 1);
			}
			ft_putendl_fd("", 1);
			ft_putendl_fd("", 1);
			if (teste[c1]->param[0])
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
				continue;
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
