/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:01:03 by cacesar-          #+#    #+#             */
/*   Updated: 2025/12/03 14:13:52 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H

# include <readline/readline.h>
# include <readline/history.h>
# define PARSE_H

typedef struct token;
typedef struct logic;

typedef struct logic
{
	char	*operator;

	token	*left;
	logic	*right;
} logic;

typedef struct token
{
	char	*cmd;
	char	*opt;
} token;

#endif;