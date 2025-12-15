/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:01:06 by cacesar-          #+#    #+#             */
/*   Updated: 2025/12/15 08:23:03 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	error(void)
{
}

void	expansion(char*l, unsigned int *c, t_list*p, unsigned int *b)
{
}

int	quotes(char*l, unsigned int *c, t_list*p, unsigned int *b)
{
	char	type;

	if (p->content)
		p->content = ft_strjoin((char *)p->content, ft_substr(l, *b, *c - 2));
	type = l[*c - 1];
	*b = *c;
	if (type == '\'')
	{
		while (l[*c] != type && l[*c])
			*c++;
		p->content = ft_strjoin((char *)p->content, ft_substr(l, *b, *c));
	}
	else if (type == '\"')
	{
		while (l[*c] != type && l[*c] && type == '\"')
			if (l[*c++] == '$')
				expansion(l, c, p, b);
		p->content = ft_strjoin((char *)p->content, ft_substr(l, *b, *c));
	}
	else
		expansion(l, c, p, b);
	*b = *c;
	if (!l[*c] && type != '$')
		return (0);
	return (1);
}

int	ft_isedcase(char l, int flag, t_logic*p)
{
	if (flag == 1 && p)
		return (l == '|' || l == '\n');
	else if (flag == 2 && p)
	{



















	}
	return (0);
}

t_list	*s_split(t_info*i, unsigned int c, unsigned int b, t_list *p)
{
	while (i->l[c] == ' ')
		c++;
	b = c;
	if (!i->l[c])
		return (p);
	p = malloc(sizeof(t_list));
	p->content = 0;
	while (i->l[c] && i->l[c] != ' ' && !ft_isedcase(i->l[c], 1, p))
		if (i->l[c] == '\"' || i->l[c] == '\'' || i->l[c++] == '$')
			if (!quotes(i->l, &c, p, &b))
				return (error);
	if (ft_isedcase(i->l[c], 1, p) && p->content)
	{
		p->content = ft_strjoin((char *)p->content, ft_substr(i->l, b, c - 1));
		p->next = ft_isedcase(i->l[c], 2, p);
		return (p);
	}
	else if (ft_isedcase(i->l[c], 1, p))
		p->content = ft_isedcase(i->l[c], 2, p);
	if (!p->content && !ft_isedcase(i->l[c], 1, p))
		p->content = ft_substr(i->l, b, c);
	else if (!ft_isedcase(i->l[c], 1, p))
		p->content = ft_strjoin((char *)p->content, ft_substr(i->l, b, c));
	p->next = s_split(i->l + c, 0, 0, 0);
	return (p);
}

t_logic	*binary_tree(char**prm)
{
}

void	env_maker(t_info*i, int c1, int c2, char**envp)
{
	while (envp[++c1])
		;
	i->env = ft_calloc(c1, 8);
	c1 = -1;
	while (envp[++c1])
		i->env[c1] = ft_strdup(envp[c1]);
	i->env[c1] = 0;
}

int	main(int argc, char**argv, char**envp)
{
	t_info	i;
	int		c;

	env_maker(&i, -1, -1, envp);
	i.flag = 1;
	while (argv && envp)
	{
		argc = -1;
		i.l = readline("Shellshock: ");
		if (!i.l)
			continue ;
		while (i.l[++argc])
			if (i.l[argc] == '\n')
				c = ++i.flag;
		i.tree = ft_calloc(i.flag + 1, 8);
		while (i.flag)
		{
			i.list = s_split(&i, 0, 0, 0);
			i.flag--;
		}
	}
	return (0);
}
