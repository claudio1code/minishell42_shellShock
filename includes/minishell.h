/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:38:07 by clados-s          #+#    #+#             */
/*   Updated: 2025/12/22 11:27:13 by clados-s         ###   ########.fr       */
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

typedef struct s_info
{
	char			**env;
	char			*l;
	char			*str;
	int				c2;
	int				rst;
	t_list			*list;

	t_logic			**tree;
}	t_info;

typedef struct s_logic
{
	char	*operator;

	t_token	*left;
	t_logic	*right;
}	t_logic;


typedef struct s_token
{
	char	*cmd;
	char	**rdc;
	char	**param;
}	t_token;

// typedef struct s_minishell
// {
// 	char	**envp; // copia das variaveis de ambiente
// 	int		exit_code; // guardar a o valor do ultimo comando $?
// }	t_minishell;

/*----------------------------------------------*/
/*------------ E X E C U T I O N ---------------*/
/*----------------------------------------------*/

char	*get_cmd_path(char *cmd, char **envp);
int		handle_redirections(char **redir);

#endif
