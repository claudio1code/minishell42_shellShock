/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:01:06 by cacesar-          #+#    #+#             */
/*   Updated: 2025/12/04 17:47:41 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"


char	*qtio(char*l, unsigned int *c1, char type, unsigned int *b)
{
}

int	ft_isedcase(char l)
{
	return (l == '|' || l == '<' || l == '>' || l == '\n');
}

t_list	*s_split(char*l, unsigned int c, unsigned int b, t_list *p)
{
	while (l[c] == ' ')
		c++;
	b = c;
	if (!l[c])
		return (p);
	p = malloc(sizeof(t_list));
	p->content = 0;
	while (l[c] && l[c] != ' ' && !ft_isedcase(l[c]))
	{
		if (l[c] == '\"' || l[c] == '\'' || l[c] == '$')
		{
			p->content = ft_substr(l, b, c);
			p->content = ft_strjoin((char *)p->content, qtio(l, &c, l[c], &b));
		}
		c++;
	}
	if (ft_isedcase(l[c]))
		c--;
	if (!(char *)p->content)
		p->content = ft_substr(l, b, c);
	else if (!ft_isedcase(l[c]))
		p->content = ft_strjoin((char *)p->content, qtio(l, &c, l[c], &b));
	p->next = s_split(l, c, 0, 0);
	return (p);
}

t_logic	*binary_tree(char**prm)
{
}

int	main(int argc, char**argv, char**envp)
{
	char	*line;

	while (argc && argv && envp)
	{
		line = readline("Shellshock: ");
		if (!line)
			continue ;
		add_history(line);
		binary_tree(s_split(line, 0, 0, 0));
	}
	return (0);
}
