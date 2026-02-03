/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:01:06 by cacesar-          #+#    #+#             */
/*   Updated: 2026/02/03 11:42:54 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//A função expansion expandi variaveis passadas e contatena elas ao
//restante do parametro se existir;
//*i = struct data;
//*p = lista linkada onde o retorno da readline sera quebrado
//em parametros para a execução;
//*c = countador usado para percorrer o retorno da readline;
//*b = countador usada para marcar o começo do parametro achado no
//retorno da readline, utilizado na ft_substr;

void	expansion(t_info*i, unsigned int *c, unsigned int *b, t_list*p)
{
	char	*var;

	if (*c - *b >= 1)
		p->content = ft_strjoin(p->content,
				ft_substr(i->l, *b, *c - *b - 1), 1, 1);
	var = var_maker(i, c, b);
	if (!ft_strncmp("?", var, 2))
			p->content = ft_strjoin(p->content, ft_itoa(i->exit_code), 1, 1);
	else
		p->content = ft_strjoin(p->content, get_env_val(i->env, var), 1, 0);
	free (var);
	*b = ++(*c);
}
//A função quotes cuida qualquer caractere q mude a leitura dos parametros,
//como '',  "" e $;
//*i = struct data;
//*p = lista linkada onde o retorno da readline sera quebrado em
//parametros para a execução;
//*c = countador usado para percorrer o retorno da readline;
//*b = countador usada para marcar o começo do parametro achado
//no retorno da readline, utilizado na ft_substr;

void	quotes(t_info*i, unsigned int *c, t_list*p, unsigned int *b)
{
	p->content = ft_strjoin(p->content,
			ft_substr(i->l, *b, *c - *b - 1), 1, 1);
	i->c2 = i->l[*c - 1];
	*b = *c;
	if (i->c2 == '\'' || i->c2 == '\"')
		p->type = 1;
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
//*p = lista linkada onde o retorno da readline sera quebrado
//em parametros para a execução;
//*c = countador usado para percorrer o retorno da readline;
//*b = countador usada para marcar o começo do parametro achado
//no retorno da readline, utilizado na ft_substr;

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
//*p = lista linkada onde o retorno da readline sera quebrado em
//parametros para a execução;
//*c = countador usado para percorrer o retorno da readline;
// b = countador usada para marcar o começo do parametro achado
//no retorno da readline, utilizado na ft_substr;

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
	p->type = 0;
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
				ft_substr(i->l, *b, *c - *b), 1, 1);
	p->next = s_split(i, c, b, 0);
	return (p);
}
//A função lexer prepara o retorno da readline para a execução;
//*i = struct data;
//*c = countador usado para percorrer o retorno da readline;
//*b = countador usada para marcar o começo do parametro achado
//no retorno da readline, utilizado na ft_substr;

void	lexer(t_info*i, unsigned int *c, unsigned int *b)
{
	int		c1;
	t_list	*t;
	t_token	*tmp;

	c1 = ft_chr_num(i->l, i);
	historic(i->l, 0);
	i->exec = ft_calloc(i->c3 + 1, 8);
	*c = 0;
	*b = 0;
	while (i->l[*c])
	{
		i->list = s_split(i, c, b, 0);
		t = i->list;
		tmp = cmd(t, i, 1, 1);
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
