/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:01:03 by cacesar-          #+#    #+#             */
/*   Updated: 2026/01/27 09:44:47 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H

# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/includes/libft.h"
# define PARSE_H

typedef struct s_token	t_token;
typedef struct s_logic	t_logic;
typedef struct s_rdc	t_rdc;

//volatile sig_atomic_t	g_sig;

typedef struct s_info
{
	char			**env;
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

typedef struct s_token
{
	int		error;
	int		bonus;
	char	*cmd;
	char	**rdc;
	char	**param;
	t_token	*next;
}	t_token;

int		error(t_token*r);
int		ft_chr_num(char*str, t_info*i);
int		cmd_prep(t_list *t, int *param, int *rdc, t_info*i);
int		edcase(t_info*i, unsigned int *c, t_list*p, unsigned int *b);
char	*var_maker(t_info*i, unsigned int *c, unsigned int *b);
void	signaler(int t);
void	historic(char	*l);
void	env_maker(t_info*i, char**envp);
void	cmd_fill(t_list*t, t_token*r, char*str);
void	lexer(t_info*i, unsigned int *c, unsigned int *b);
void	quotes(t_info*i, unsigned int *c, t_list*p, unsigned int *b);
void	expansion(t_info*i, unsigned int *c, unsigned int *b, t_list*p);
t_list	*s_split(t_info*i, unsigned int *c, unsigned int *b, t_list *p);
t_token	*cmd(t_list	*t, t_info*i, int param, int rdc);

#endif