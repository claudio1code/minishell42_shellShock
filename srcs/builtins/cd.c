/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:23:31 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/27 15:19:15 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**/
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


static void	print_error_cd(char *arg, char *msg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
}
static int	aux_cd(t_info *info, t_token *token, char *path)
{
	if (!token->param[1])
	{
		path = get_env_val(info->env, "HOME");
		if (!path)
		{
			ft_putendl_fd("minishell: cd : HOME not set", 2);
			return (1);
		}
	}
	else if (!ft_strncmp(token->param[1], "-", 2))
	{
		path = get_env_val(info->env, "OLDPWD");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (1);
		}
		printf("%s\n", path);
	}
	else
		path = token->param[1];
	return (0);
}
int	mini_cd(t_info *info, t_token *token)
{
	char	*path;
	int		ret;

	path = NULL;
	aux_cd(info, token, path);
	ret = chdir(path);
	if (ret)
	{
		print_error_cd(token->param[1], "No such file or directory");
		return (1);
	}
	update_pwd(info);
	return (0);
}
