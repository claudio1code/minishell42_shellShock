/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd..c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:45:12 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/13 13:08:17 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*percorro o arrays de parâmetros, caso tenha mais
de 1 parâmetro, imprimo mensagem de erro, dps guardo 
o diretório atual com o getcwd() e printo*/
int	pwd(t_token *token)
{
	int		i;
	char	*cwd;

	i = 0;

	while (token->param[i])
		i++;
	if (i > 1)
	{
		ft_putstr_fd("pwd: too many arguments", 1);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	free(cwd);
	return (0);
}
