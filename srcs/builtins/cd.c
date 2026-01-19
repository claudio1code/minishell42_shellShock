/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:23:31 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/15 08:40:26 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*essa função vai faz a execução do cd, primeiro guarda o oldpwd
em uma variavel, e faz uma syscall e verifica se ocorreu tudo bem, 
caso não tenha, imprime msg de erro e libera a memória do oldpwd,
caso passe, chama a função que atualiza a variavel de ambiente e 
atualiza o newpwd tbm	
*/
static int	change_dir(t_info *info, char *path, int print_path)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(path))
	{
		ft_putstr_fd("minishell: cd:", 2);
		ft_putstr_fd(path, 2);
		perror(" ");
		free(old_pwd);
		return (1);
	}
	if (old_pwd)
		update_env(info, "OLDPWD", old_pwd, 1);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		update_env(info, "PWD", new_pwd, 0);
		if (print_path)
			printf("%s\n", new_pwd);
		// free(new_pwd);
	}
	return (0);
}

int	mini_cd(t_info *info, t_token *token)
{
	char	*path;
	
	if (!token->param[1] || !ft_strncmp(token->param[1], "~", 2))
	{
		path = get_env_value(info->env, "HOME");
		if (!path)
		{
			ft_putendl_fd("minishell: cd : HOME not set", 2);
			return (1);
		}
		return (change_dir(info, path, 0));
	}
	if (!ft_strncmp(token->param[1], "-", 2))
	{
		path = get_env_value(info->env, "OLDPWD");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (1);
		}
		return (change_dir(info, path, 1));
	}
	return (change_dir(info, token->param[1], 0));
}
