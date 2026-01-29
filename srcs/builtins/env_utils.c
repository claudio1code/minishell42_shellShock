/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:05:29 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/27 10:55:15 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*função auxiliar que vai pegar o value do caminho na 
variavel de ambiente EX: o key = HOME,  então seria
HOME=/home/user ela pegaria tudo que esta dps do '='*/
// char	*get_env_value(char **env, char *key)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = ft_strlen(key);
// 	while (env[i])
// 	{
// 		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
// 			return (env[i] + len + 1);
// 		i++;
// 	}
// 	return (NULL);
// }

char	*get_env_val(t_hashtable *table, char *key)
{
	unsigned long	idx;
	t_env_node		*tmp;

	idx = ft_hashtable(key);
	tmp = table->buckets[idx];
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

/* Converte a hashtable para char ** (formato KEY=VALUE) para o execve */
char	**ht_to_matrix(t_hashtable *env)
{
	char		**matrix;
	t_env_node	*tmp;
	int			i;
	int			j;

	matrix = malloc(sizeof(char *) * (env->count + 1));
	if (!matrix)
		return (NULL);
	i = 0;
	j = 0;
	while (i < TABLE_SIZE)
	{
		tmp = env->buckets[i];
		while (tmp)
		{
			matrix[j] = ft_triple_strjoin(tmp->key, "=", tmp->value); 
			j++;
			tmp = tmp->next;
		}
		i++;
	}
	matrix[j] = NULL;
	return (matrix);
}

/*função que add uma nova variável no env, ela é uma segurança
para um caso expecifico, por exemplo o usuario da um 'unset OLDPWD'
e logo em seguida dá um 'cd /arquivos' e dps 'cd -', ele não teria
onde salvar o caminho, entao basicamente eu calloco o tamanho do env
mais 2 que seria da nova variavel e do null, dou free no ponteiro da
antiga variavel e aponto pra new env que copiou tudo e add a nova*/
void	add_to_env(t_info *info, char *new_entry)
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
o PWD e OLDPWD ou crio caso não tenha*/
void	update_env(t_info *info, char *key, char *value, int flag)
{
	int		i;
	int		len;
	char	*new_entry;
	char	*temp;

	len = ft_strlen(key);
	temp = ft_strjoin(key, "=", 0, 0);
	if (value)
		new_entry = ft_strjoin(temp, value, 1, 0);
	else
		new_entry = ft_strdup(temp);
	i = 0;
	while (info->env[i])
	{
		if (!ft_strncmp(info->env[i], key, len) && info->env[i][len] == '=')
		{
			free(info->env[i]);
			info->env[i] = new_entry;
			if (!flag && value)
				free(value);
			return ;
		}
		i++;
	}
	add_to_env(info, new_entry);
	if (flag && value)
		free(value);
}


