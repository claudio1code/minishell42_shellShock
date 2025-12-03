/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:01:06 by cacesar-          #+#    #+#             */
/*   Updated: 2025/12/03 18:09:05 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"


int	param_counter(char*l, int c1)
{
	int		n;
	char	type;
	int		flag;

	n = 0;
	flag = 0;
	while (l[c1])
	{
		while (l[c1] == ' ')
			c1++;
		while (l[c1])
		{
			if (l[c1] == '\'' || l[c1] == '\"')
			{
				type = l[c1];
				flag = 1;
			}
			else if (l[c1] == ' ')
			{
				n++;
				break ;
			}
			c1++;
		}
	}
}

char	**s_split(char*l, int c1)
{
	char	*beg;
	char	*end;

	add_history(l);
	while (l[c1] == ' ')
		c1++;
	while (l[c1])
	{
	}
	free(l);
}

t_logic	*binary_tree(char**prm)
{
}

int	main(int argc, char**argv, char**envp)
{
	char	*line;

	argc = 0;
	envp = 0;
	argv = 0;
	while (1)
	{
		line = readline("Shellshock: ");
		param_counter(line, 0);
		binary_tree(s_split(line, 0));
	}
	return (0);
}
