/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:01:06 by cacesar-          #+#    #+#             */
/*   Updated: 2025/12/18 19:21:06 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	error(void)
{
}

void	expansion(t_info*i, unsigned int *c, t_list*p, unsigned int *b)
{
	
}

void	quotes(t_info*i, unsigned int *c, t_list*p, unsigned int *b)
{
	char	type;

	i->str = (char *)p->content;
	if (i->str && i->str[*c - 2] != '\'' && i->str[*c - 2] != '\"')
		i->str = ft_strjoin(i->str, ft_substr(i->l, *b, *c - *b - 2), 1, 1);
	else if (*c - *b >= 2)
		i->str = ft_substr(i->l, *b, *c - *b - 1);
	type = i->l[*c - 1];
	*b = *c;
	if (type == '\'')
	{
		while (i->l[*c] != type && i->l[*c])
			*c++;
		i->str = ft_strjoin(i->str, ft_substr(i->l, *b, *c - *b), 1, 1);
	}
	else if (type == '\"')
	{
		while (i->l[*c] != type && i->l[*c] && type == '\"')
			if (i->l[*c++] == '$')
				expansion(i, c, p, b);
		i->str = ft_strjoin(i->str, ft_substr(i->l, *b, *c), 1, 1);
	}
	else
		expansion(i, c, p, b);
	*b = *c;
}

void	edcase(t_info*i, unsigned int *c, t_list*p, unsigned int *b)
{
	i->c2 = i->l[*c];
	if (p->content && *c - *b >= 1)
		p->content = ft_strjoin(i->str, ft_substr(i->l, *b, *c - *b - 1), 1, 1);
}

t_list	*s_split(t_info*i, unsigned int *c, unsigned int b, t_list *p)
{
	while (i->l[*c] == ' ')
		*c++;
	b = *c;
	if (!i->l[*c] || i->l[*c] == '\n')
		return (p);
	p = malloc(sizeof(t_list));
	p->content = 0;
	while (i->l[*c] && i->l[*c] != ' ' && !ft_strchr("&|<>\n", i->l[*c]))
		if (ft_strchr("\'\"$", i->l[*c++]))
			quotes(i->l, c, p, &b);
	if (ft_strchr("&|<>\n", i->l[*c]))
		edcase(i, c, p, &b);
	if (ft_strchr("&|<>\n", i->l[*c]))
		return (p);
	if (!p->content && !ft_strchr("&|<>\n", i->l[*c]))
		p->content = ft_substr(i->l, b, *c - b);
	else if (!ft_strchr("&|<>\n", i->l[*c]))
		p->content = ft_strjoin(p->content, ft_substr(i->l, b, *c - b), 1, 1);
	p->next = s_split(i, c, 0, 0);
	return (p);
}

t_logic	*binary_tree(t_list*s_split)
{
}

void	env_maker(t_info*i, int c1, int c2, char**envp)
{
	while (envp[++c1])
		;
	i->env = ft_calloc(c1 + 1, 8);
	c1 = -1;
	while (envp[++c1])
		i->env[c1] = ft_strdup(envp[c1]);
	i->env[c1] = 0;
	i->rst = 0;
}

int ft_chr_num(char*str, int c , int result, t_info*i)
{
	while (str[++c])
		if (str[c] == '\n')
			result++;
	i->c2 = result;
	return (result);
}

int	main(int argc, char**argv, char**envp)
{
	t_info	data;
	int		c1;

	env_maker(&data, -1, -1, envp);
	while (argv && envp)
	{
		argc = 0;
		data.l = readline("Shellshock: ");
		if (!data.l)
			continue ;
		c1 = ft_chr_num(data.l, -1, 1, &data);
		data.tree = ft_calloc(data.c2 + 1, 8);
		while (c1)
		{
			data.list = s_split(&data, &argc, 0, 0);
			data.tree[data.c2 - c1] = binary_tree(data.list);
			ft_lstclear(&data, ft_del);
			c1--;
		}
	}
	return (0);
}
