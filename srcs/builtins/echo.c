/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:34:26 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/08 11:19:04 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*aux que verifica se o echo tem alguma flag -n*/
static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/*recebo o token do comando echo e verific 
passo todas as flags -n e seto para zero */
int	mini_echo(t_token *token)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	while (token->param[i] && is_n_flag(token->param[i]))
	{
		nl = 0;
		i++;
	}
	while (token->param[i])
	{
		ft_putstr_fd(token->param[i], 1);
		if (token->param[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (nl)
		ft_putstr_fd("\n", 1);
	return (0);
}
