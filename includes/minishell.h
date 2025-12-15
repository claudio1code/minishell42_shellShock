/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 13:12:53 by clados-s          #+#    #+#             */
/*   Updated: 2025/12/12 14:34:35 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_REDIRECT
}	t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
	int				fd_in;
	int				fd_out;
}	t_ast;

#endif