/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:01:03 by cacesar-          #+#    #+#             */
/*   Updated: 2025/12/18 12:04:37 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/includes/libft.h"
# define PARSE_H

typedef struct s_token	t_token;
typedef struct s_logic	t_logic;

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

#endif