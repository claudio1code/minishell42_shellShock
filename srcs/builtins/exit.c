/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:41:33 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/28 18:24:43 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// /* Retorna o código de saída depois de verificar se o argumento é numérico */
// static int	get_exit_code(char *arg)
// {
// 	unsigned long	res;

// 	if(!is_numeric_str(arg))
// 	{
// 		err_numeric(arg);
// 		return (-1);
// 	}
// 	res = ft_atol(arg);
// 	return (res % 256);
// }

/* Aqui só verifico se há argumento, se tiver vejo se é numérico
 se for eu retorno o número modulo de 256 ou na saída 2 caso não seja numérico,
 se for sem argumento só limpa tudo e retorna o status */
int	mini_exit(t_token *token, t_info *info)
{
	int	status;

	status = info->exit_code;
	printf("exit\n");
	if (token->param[1])
	{
		if (!is_numeric_str(token->param[1]))
		{
			status = 2;
			err_numeric(token->param[1]);
		}
		else if (token->param[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			info->exit_code = 1;
			return (1);
		}
		else
			status = ft_atol(token->param[1]) % 256;
	}
	clean_shell(info);
	return (status);
}
