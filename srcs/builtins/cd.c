/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:23:31 by clados-s          #+#    #+#             */
/*   Updated: 2026/02/06 18:08:10 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*atualizo o pwd e o old no env*/
static void	update_pwd(t_info *info)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = get_env_val(info->env, "pwd");
	new_pwd = getcwd(NULL, 0);
	if (old_pwd)
		update_hash(info->env, "OLDPWD", old_pwd);
	if (new_pwd)
	{
		update_hash(info->env, "PWD", new_pwd);
		free(new_pwd);
	}
}

/*função auxiliar do cd que retorna o path da home ou do oldpwd,
tbm já cuido caso o path n exita, por exemplo no caso de usarem 
o unset no $HOME ou $OLDPWD ou se */
static char	*aux_cd(t_info *info, t_token *token)
{
	char	*path;

	if (!token->param[1] || !ft_strncmp(token->param[1], "~", 2))
	{
		path = get_env_val(info->env, "HOME");
		if (!path)
			ft_putendl_fd("minishell: cd : HOME not set", 2);
		return (path);
	}
	if (!ft_strncmp(token->param[1], "-", 2))
	{
		path = get_env_val(info->env, "OLDPWD");
		if (!path)
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		else
			printf("%s\n", path);
		return (path);
	}
	return (token->param[1]);
}

int	mini_cd(t_info *info, t_token *token)
{
	char	*path;

	path = aux_cd(info, token);
	if (!path)
		return (1);
	if (token->param[2])
	{
		print_error_cd(token->param[1], "too many arguments");
		return (1);
	}
	if (chdir(path))
	{
		print_error_cd(token->param[1], "No such file or directory");
		return (1);
	}
	update_pwd(info);
	return (0);
}
