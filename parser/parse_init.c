/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:01:06 by cacesar-          #+#    #+#             */
/*   Updated: 2025/12/03 16:56:30 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"



char	**s_split(char*l, int c1)
{
	char	*beg;
	char	*end;

	add_history(l);
	while (l[c1] == ' ')
		c1++;
	while (l[c1])
	{
		beg = &l[c1];
		
	}
	free(l);
}

t_logic	*binary_tree(char**prm)
{
}

int	main(int argc, char**argv, char**envp)
{
	argc = 0;
	envp = 0;
	argv = 0;
	while (1)
		binary_tree(s_split(readline("shellshock: "), 0));
	return (0);
}
