/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:23:31 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/09 11:31:23 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*função auxiliar que vai pegar o value do caminho na 
variavel de ambiente EX: o key = HOME,  então seria
HOME=/home/user ela pegaria tudo que esta dps do '='*/
static char	*get_env_value(char **env, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == "=")
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

/*função que add uma nova variável no env, ela é uma segurança
para um caso expecifico, por exemplo o usuario da um 'unset OLDPWD'
e logo em seguida dá um 'cd /arquivos' e dps 'cd -', ele não teria
onde salvar o caminho, entao basicamente eu calloco o tamanho do env
mais 2 que seria da nova variavel e do null, dou free no ponteiro da
antiga variavel e aponto pra new env que copiou tudo e add a nova*/
static void	add_to_env(t_info *info, char *new_entry)
{
	int		i;
	char	**new_env;

	i = 0;
	while (info->env[i])
		i++;
	new_env = ft_calloc(sizeof(char *), (i + 2));
	if (!new_env)
		return ;
	i = 0;
	while (info->env[i])
	{
		new_env[i] = info->env[i];
		i++;
	}
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	free(info->env);
	info->env = new_env;
}

/*Essa função ela atualiza o env, cada vez que mudo de diretorio atualizo
o PWD e OLDPWD*/
static void	update_env(t_info *info, char *key, char *value)
{
	int		i;
	int		len;
	char	*new_entry;
	char	*temp;

	len = ft_strlen(key);
	temp = ft_strjoin(key, "=", 0, 0);
	new_entry = ft_strjoin(temp, value, 1, 0);
	i = 0;
	while (info->env[i])
	{
		if (!ft_strncmp(info->env[i], key, len) && info->env[i][len] == '=')
		{
			free(info->env[i]);
			info->env[i] = new_entry;
			return ;
		}
		i++;
	}
	add_to_env(info, new_entry);
}

static int	change_dir(t_info *info, char *path, int print_path)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!getcwd (path))
	{
		ft_putstr_fd("", 2)
	}
	
}

int	mini_cd(t_info *info, t_token *token)
{
	
}
