/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 13:12:53 by clados-s          #+#    #+#             */
/*   Updated: 2025/12/19 14:39:17 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

typedef enum e_type
{
	T_ARGS_CMD, //CCOMANDOS E ARGUMENTOS
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC
}	t_type;

//Sugestão para a estrutura dos tokens e redirects
typedef struct s_redir
{
	t_type			type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_token
{
	t_type			type; // (ex:   "t_args" "t_redir" "t_args" "t_redout")
	char			**par; // (ex:   "ls"      "<"      "oi"      >" )
	struct s_redir	*redir;
}	t_token;


typedef struct s_ast //abstract struct tree
{
	t_type			type;
	char			**args;
	t_redir			*redirs;
	struct s_ast	*left; // se a gente for fazer bonus
	struct s_ast	*right;// idem
	int				fd_in;
	int				fd_out;
}	t_ast;

typedef struct s_minishell
{
	char	**envp; // copia das variaveis de ambiente
	int		exit_code; // vai guardar a o valor do ultimo comando $?
}	t_minishell;

/*----------------------------------------------*/
/*------------ E X E C U T I O N ---------------*/
/*----------------------------------------------*/

char	*get_cmd_path(char *cmd, char **envp);

#endif

 