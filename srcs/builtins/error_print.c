/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 18:01:08 by clados-s          #+#    #+#             */
/*   Updated: 2026/02/04 16:03:04 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error_cd(char *arg, char *msg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
}

/* Printa erro de argumento não numérico */
void	err_numeric(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

void	err_invalid_export(char *arg, char *key, char *value)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	free(key);
	free(value);
}

void	print_erro(t_token *token, t_info *info)
{
	if (!token->param || !token->param[0] || !token->param[0][0])
		ft_putstr_fd("''", 2);
	else
		ft_putstr_fd(token->param[0], 2);
	ft_putendl_fd(": command not found", 2);
	clean_shell(info);
	exit(127);
}
