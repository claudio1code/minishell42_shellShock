/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:15:46 by clados-s          #+#    #+#             */
/*   Updated: 2026/02/03 16:53:09 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern volatile sig_atomic_t	g_sig;

/*crio um arquivo temporario onde vai ser escrito o heredoc, inicia a linha com
"> ", caso dê uma ctrl +d ele printa  um warning e sai, dps d tudo garanto que
od fd seja fechado e retorne o fd do arquivo temporario*/
static void	loop_heredoc(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		g_sig = 0;
		line = readline("> ");
		if (g_sig == 130)
		{
			if (line)
				free(line);
			break ;
		}
		if (!line)
		{
			error_heredoc(delimiter);
			break ;
		}
		if (!ft_strcmp(line, delimiter))
		{
			free (line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

/*só pra criar arquivos temporarios unico tipo temp_0, temp_1
pq antes se eu desse << here << here o segundo heredoc apagava
o primeiro temp */
static char	*get_hd_name(void)
{
	static int	i;
	char		*num;
	char		*name;

	num = ft_itoa(i++);
	name = ft_strjoin(".heredoc_", num, 0, 1);
	return (name);
}

/*a função vai abrir o arquivo temporario e executar o heredoc 
se tiver um ctrl C ele remove o arquivo temporario e retorna -1*/
static int	exec_one_heredoc(char *delimiter, char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	loop_heredoc(fd, delimiter);
	close(fd);
	return (0);
}

static int	free_negative(char *name)
{
	free(name);
	return (-1);
}

/*a função vai percorrer os tokens e preparar os heredocs.
para cada heredoc, cria um arquivo temporário e executa o heredoc
e transforma o << em < */
int	prepare_heredocs(t_token *token)
{
	int		i;
	char	*name;

	while (token)
	{
		i = 0;
		while (token->rdc && token->rdc[i])
		{
			if (!ft_strncmp(token->rdc[i], "<<", 3))
			{
				name = get_hd_name();
				if (exec_one_heredoc(token->rdc[i + 1], name) == -1)
					return (free_negative(name));
				free(token->rdc[i]);
				token->rdc[i] = ft_strdup("<");
				free(token->rdc[i + 1]);
				token->rdc[i + 1] = name;
			}
			i += 2;
		}
		token = token->next;
	}
	return (0);
}
