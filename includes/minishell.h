/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:01:03 by cacesar-          #+#    #+#             */
/*   Updated: 2026/01/29 14:10:27 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>

# define TABLE_SIZE 100

typedef struct s_token		t_token;
typedef struct s_env_node	t_env_node;
typedef struct s_hashtable	t_hashtable;
typedef struct s_info		t_info;

extern volatile sig_atomic_t		g_sig;

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
	t_hashtable		*env;
	char			*l;
	char			*str;
	int				error;
	int				bonus;
	unsigned int	count;
	unsigned int	begin;
	int				c2;
	int				c3;
	int				exit_code;
	t_list			*list;
	t_token			**exec;
}	t_info;



/*----------------------------------------------*/
/*------------ E X E C U T I O N ---------------*/
/*----------------------------------------------*/

int				error(t_token*r);
int				pwd(t_token *token);
int				mini_env(t_info *info);
int				is_builtins(char *cmd);
int				is_numeric_str(char *str);
int				mini_echo(t_token *token);
int				count_vars(t_hashtable *env);
int				ft_chr_num(char*str, t_info*i);
int				handle_redirections(t_token *token);
int				mini_cd(t_info *info, t_token *token);
int				mini_exit(t_token *token, t_info *info);
int				mini_unset(t_token *token, t_info *info);
int				mini_export(t_token *token, t_info *info);
int				exec_bultin(t_token *token, t_info *info);
int				cmd_prep(t_list *t, int *param, int *rdc, t_info*i);
int				edcase(t_info*i, unsigned int *c, t_list*p, unsigned int *b);
char			**ht_to_matrix(t_hashtable *env);
char			*get_env_val(t_hashtable *env, char *key);
char			*get_cmd_path(char *cmd, t_hashtable *env);
char			*get_env_val(t_hashtable *table, char *key);
char			*var_maker(t_info*i, unsigned int *c, unsigned int *b);
void			signaler(int t);
void			historic(char	*l);
void			err_numeric(char *arg);
void			clean_shell(t_info *info);
void			child_cleanup(char *path);
void			env_maker(t_info*i, char**envp);
void			free_hashtable(t_hashtable *table);
void			print_error_cd(char *arg, char *msg);
void			exec_cmd(t_token *token, t_info *info);
void			cmd_fill(t_list*t, t_token*r, char*str);
void			add_to_env(t_info *info, char *new_entry);
void			init_env_table(t_info *info, char **envp);
void			exec_pipeline(t_token *token, t_info *info);
void			lexer(t_info*i, unsigned int *c, unsigned int *b);
void			err_invalid_export(char *arg, char *key, char *value);
void			update_hash(t_hashtable *table, char *key, char *value);
void			update_env(t_info *info, char *key, char *value, int flag);
void			quotes(t_info*i, unsigned int *c, t_list*p, unsigned int *b);
void			expansion(t_info*i, unsigned int *c, unsigned int *b, t_list*p);
t_list			*s_split(t_info*i, unsigned int *c, unsigned int *b, t_list *p);
t_token			*cmd(t_list	*t, t_info*i, int param, int rdc);
t_env_node		*new_env_node(char *key, char *value);
unsigned long	ft_hashtable(char *key);

#endif