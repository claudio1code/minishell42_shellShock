/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftlurker <ftlurker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:01:03 by cacesar-          #+#    #+#             */
/*   Updated: 2026/01/17 08:13:36 by ftlurker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/includes/libft.h"
# define PARSE_H

typedef struct s_token	t_token;
typedef struct s_logic	t_logic;
typedef struct s_rdc	t_rdc;

typedef struct s_rdc
{
	char	*rdc;
	t_rdc	*next;
}	t_rdc;

typedef struct s_info
{
	char			**env;
	char			*l;
	char			*str;
	int				error;
	unsigned int	count;
	int				c2;
	int				c3;
	int				exit;
	t_list			*list;

	t_logic			**tree;
}	t_info;

typedef struct s_logic
{
	char	*operator;

	t_token	*cmd;
	t_logic	*right;
	t_logic	*left;
}	t_logic;

typedef struct s_token
{
	char	**param;
	t_rdc	*rdc;
}	t_token;

#endif