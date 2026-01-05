/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:38:07 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/05 14:41:43 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

// typedef enum e_type
// {
// 	T_ARGS_CMD, //CCOMANDOS E ARGUMENTOS
// 	T_PIPE,
// 	T_REDIR_IN,
// 	T_REDIR_OUT,
// 	T_APPEND,
// 	T_HEREDOC
// }	t_type;

typedef struct s_token
{
	char	*cmd;
	char	**rdc;
	char	**param;
}	t_token;

typedef struct s_logic
{
	char			*operator;
	struct s_logic	*left;
	struct s_logic	*right;
	t_token			*cmd;
}	t_logic;

typedef struct s_info
{
	char			**env;
	char			*l;
	char			*str;
	int				c2;
	int				exit_code;
	t_list			*list;

	t_logic			**tree;
}	t_info;



/*----------------------------------------------*/
/*------------ E X E C U T I O N ---------------*/
/*----------------------------------------------*/

char	*get_cmd_path(char *cmd, char **envp);
int		handle_redirections(char **redir);
void	child_cleanup(char *path);
void	exec_cmd(t_token *token, t_info *info);
void	exec_tree(t_logic *node, t_info *info);
int		is_builtins(char *cmd);
int		exec_bultin(t_token *token);
int		mini_echo(t_token *token);


#endif
