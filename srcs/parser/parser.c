/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 09:14:00 by cacesar-          #+#    #+#             */
/*   Updated: 2026/01/30 15:02:46 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//A funcção historic adiciona as saidas do readline ao historico
//*l = retorno da readline;

void	historic(char	*l)
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

//A função cmd_fill passa o conteudo da lista linkada
//criada pelo lexer para a lista da execução;
//*t = ponteiro separado paro o retorno do lexer,
//para poder percorrer sem perder o inicio;
//*r = lista linkada q sera passa para execução;

void	cmd_fill(t_list*t, t_token*r, char*str)
{
	int	c1;
	int	c2;

	c1 = 0;
	c2 = 0;
	while (t && ((char *)t->content)[0] != '|' &&
		((char *)t->content)[0] != '&')
	{
		str = t->content;
		if (!t->type && (str[0] == '<' || str[0] == '>'))
		{
			r->rdc[c1++] = ft_strdup(t->content);
			t = t->next;
			if (t)
				r->rdc[c1++] = ft_strdup(t->content);
		}
		else if (!ft_strchr("&|<>", str[0]) || t->type)
		{
			if (!c2)
				r->cmd = ft_strdup(t->content);
			r->param[c2++] = ft_strdup(t->content);
		}
		if (t)
			t = t->next;
	}
}

//A função cmd_prep me usada para pegar informações necessarias para a
//callocação das variaveis da lista linkada q sera utilizada na execução,
//alem servir como checagem de syntaxe;
//*t = ponteiro separado paro o retorno do lexer,
//para poder percorrer sem perder o inicio;
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
		if (!t->type && ((str[0] == '<' && len > 3)
				|| (str[0] == '>' && len > 2)
				|| (str[0] == '&' && len != 2) || (str[0] == '|' && len > 2)
				|| ((str[0] == '<' || str[0] == '>')
					&& (!t->next || ((char *)t->next->content)[0] == '|'))))
			i->error = 1;
		if (str[0] == '&' || (str[0] == '|' && len == 2))
			i->bonus = 1;
		if (!ft_strchr("&|<>", str[0]) && !t->type)
			(*param)++;
		if (str[0] == '|' || str[0] == '&')
			len = -42;
		t = t->next;
	}
	return (i->error || i->bonus); /*leak*/
}

//A função cmd cria o array de listas linkadas t_token para a execução;
//*t = ponteiro separado paro o retorno do lexer, para poder percorrer
//sem perder o inicio;
//*i = struct data;

t_token	*cmd(t_list	*t, t_info*i, int param, int rdc)
{
	t_token	*r;

	r = 0;
	if (!t)
		return (0);
	cmd_prep(t, &param, &rdc, i);
	param = (param > rdc) * (param - rdc);
	r = malloc(sizeof(t_token));
	r->error = i->error;
	r->bonus = i->bonus;
	i->error = 0;
	i->bonus = 0;
	r->cmd = 0;
	r->param = calloc(param + 1, 8);
	r->rdc = calloc(rdc + rdc + 1, 8);
	cmd_fill(t, r, 0);
	while (t && ((char *)t->content)[0] != '|' &&
		((char *)t->content)[0] != '&')
		t = t->next;
	if (t && (((char *)t->content)[0] == '|'
		|| ((char *)t->content)[0] == '&'))
		t = t->next;
	r->next = cmd(t, i, 1, 1);
	return (r);
}

//A função error checa se ouve erros de syntaxe;

int	error(t_token*r)
{
	if (r->error)
		ft_putendl_fd("Syntax Error", 1);
	if (r->bonus)
		ft_putendl_fd("I'm sorry but we are suffering from xXxSHELLSHOCKxXx",
			1);
	return (r->error || r->bonus);
}
