/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:38:07 by clados-s          #+#    #+#             */
/*   Updated: 2026/01/20 13:00:41 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

typedef struct s_token
{
	char	*cmd;
	char	**rdc;
	char	**param;
	struct s_token	*next;
}	t_token;


typedef struct s_info
{
	char			**env;
	char			*l;
	char			*str;
	int				c2;
	int				exit_code;
	t_list			*list;

}	t_info;



/*----------------------------------------------*/
/*------------ E X E C U T I O N ---------------*/
/*----------------------------------------------*/

char	*get_cmd_path(char *cmd, char **envp);
int		handle_redirections(t_token *token);
void	child_cleanup(char *path);
void	exec_cmd(t_token *token, t_info *info);
void	exec_pipeline(t_token *token, t_info *info);
int		is_builtins(char *cmd);
int		exec_bultin(t_token *token, t_info *info);
int		mini_echo(t_token *token);
int		mini_cd(t_info *info, t_token *token);
int		pwd(t_token *token);
char	*get_env_value(char **env, char *key);
void	add_to_env(t_info *info, char *new_entry);
void	update_env(t_info *info, char *key, char *value, int flag);
int		mini_export(t_token *token, t_info *info);

#endif
