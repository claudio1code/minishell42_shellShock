/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftlurker <ftlurker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:01:03 by cacesar-          #+#    #+#             */
/*   Updated: 2026/01/19 06:53:08 by ftlurker         ###   ########.fr       */
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
	int				exit;
	t_list			*list;

	t_token			**exec;
}	t_info;

typedef struct s_token
{
	char	**rdc;
	char	*cmd;
	char	**param;
	t_token	*next;
}	t_token;

#endif