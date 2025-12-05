/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:01:03 by cacesar-          #+#    #+#             */
/*   Updated: 2025/12/05 12:46:19 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/includes/libft.h"
# define PARSE_H

typedef struct s_token	t_token;
typedef struct s_logic	t_logic;

typedef struct s_logic
{
	char	*operator;

	t_token	*left;
	t_logic	*right;
}	t_logic;

typedef struct s_token
{
	char	*cmd;
	char	**opt;
	char	**param;
}	t_token;

typedef enum t_node_type
{
	
}	t_node_type;


#endif