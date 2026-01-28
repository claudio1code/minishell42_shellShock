/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:38:07 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/28 11:38:56 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# define TABLE_SIZE 100

typedef struct s_token		t_token;
typedef struct s_env_node	t_env_node;
typedef struct s_hashtable	t_hashtable;
typedef struct s_info		t_info;

typedef struct s_token
{
	int		error;
	int		bonus;
	int		in;
	int		out;
	char	*cmd;
	char	**rdc;
	char	**param;
	t_token	*next;
	t_token	*prev;

}	t_token;

typedef struct s_env_node
{
	char		*key;
	char		*value;
	t_env_node	*next;
	t_env_node	*next_global;
}	t_env_node;

typedef struct s_hashtable
{
	t_env_node	*buckets[TABLE_SIZE];
	t_env_node	*head_ordered;
	t_env_node	*tail_ordered;
	int			count;
}	t_hashtable;


typedef struct s_info
{
	t_hashtable	*env;
	char		*l;
	char		*str;
	int			c2;
	int			exit_code;
	t_list		*list;
	t_token		**exec;

}	t_info;



/*----------------------------------------------*/
/*------------ E X E C U T I O N ---------------*/
/*----------------------------------------------*/

char			*get_cmd_path(char *cmd, t_hashtable *env);
int				handle_redirections(t_token *token);
void			child_cleanup(char *path);
void			exec_cmd(t_token *token, t_info *info);
void			exec_pipeline(t_token *token, t_info *info);
int				is_builtins(char *cmd);
int				exec_bultin(t_token *token, t_info *info);
int				mini_echo(t_token *token);
int				mini_cd(t_info *info, t_token *token);
int				pwd(t_token *token);
int				mini_env(t_info *info);
int				mini_export(t_token *token, t_info *info);
void			update_hash(t_hashtable *table, char *key, char *value);
int				mini_unset(t_token *token, t_info *info);
t_env_node		*new_env_node(char *key, char *value);
unsigned long	ft_hashtable(char *key);
t_env_node		*new_env_node(char *key, char *value);
void			free_hashtable(t_hashtable *table);
int				is_numeric_str(char *str);
void			clean_shell(t_info *info);
void			err_numeric(char *arg);
int			mini_exit(t_token *token, t_info *info);
char			**ht_to_matrix(t_hashtable *env);
char			*get_env_val(t_hashtable *env, char *key);
char			**ht_to_matrix(t_hashtable *env);
void			init_env_table(t_info *info, char **envp);
int				count_vars(t_hashtable *env);

#endif
