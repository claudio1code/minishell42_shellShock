/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:01:06 by cacesar-          #+#    #+#             */
/*   Updated: 2025/12/19 16:59:18 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	expansion(t_info*i, unsigned int *c, t_list*p, unsigned int *b)
{
	
}

void	quotes(t_info*i, unsigned int *c, t_list*p, unsigned int *b)
{
	i->str = (char *)p->content;
	if (i->str && i->str[*c - 2] != '\'' && i->str[*c - 2] != '\"')
		i->str = ft_strjoin(i->str, ft_substr(i->l, *b, *c - *b - 2), 1, 1);
	else if (*c - *b >= 2)
		i->str = ft_substr(i->l, *b, *c - *b - 1);
	i->c2 = i->l[*c - 1];
	*b = *c;
	if (i->c2 == '\'')
	{
		while (i->l[*c] != i->c2 && i->l[*c])
			*c++;
		i->str = ft_strjoin(i->str, ft_substr(i->l, *b, *c - *b), 1, 1);
	}
	else if (i->c2 == '\"')
	{
		while (i->l[*c] != i->c2 && i->l[*c] && i->c2 == '\"')
			if (i->l[*c++] == '$')
				expansion(i, c, p, b);
		i->str = ft_strjoin(i->str, ft_substr(i->l, *b, *c), 1, 1);
	}
	else
		expansion(i, c, p, b);
	if (i->str[*c])
		i->error = 1;
	*b = *c++;
}

int	edcase(t_info*i, unsigned int *c, t_list*p, unsigned int *b)
{
	i->c2 = i->l[*c];
	if (p->content && *c - *b >= 1)
		p->content = ft_strjoin(i->str, ft_substr(i->l, *b, *c - *b - 1), 1, 1);
	else if (*c - *b >= 1)
		p->content = ft_substr(i->l, *b, *c - *b - 1);
	if (p->content)
		return (1);
	while (i->l[*c] == i->c2)
		*c++;
	p->content = ft_substr(i->l, *b, *c - *b - 1);
	*b = *c;
	return (1);
}

t_list	*s_split(t_info*i, unsigned int *c, unsigned int b, t_list *p)
{
	int	end;

	end = 0;
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
		end = edcase(i, c, p, &b);
	if (!p->content && !ft_strchr("&|<>\n", i->l[*c]) && !end)
		p->content = ft_substr(i->l, b, *c - b);
	else if (!ft_strchr("&|<>\n", i->l[*c]) && !end)
		p->content = ft_strjoin(p->content, ft_substr(i->l, b, *c - b), 1, 1 );
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
	i->exit = 0;
	i->error = 0;
}

int ft_chr_num(char*str, int c , int result, t_info*i)
{
	while (str[++c])
		if (str[c] == '\n')
			result++;
	i->c2 = result;
	return (result);
}

void historic(char	*l, int c1, int b)
{
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

	env_maker(&data, -1, -1, envp);
	while (argv && envp)
	{
		argc = 0;
		data.l = readline("Shellshock: ");
		if (!data.l)
			continue ;
		c1 = ft_chr_num(data.l, -1, 1, &data);
		historic(data.l, 0, 0);
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
