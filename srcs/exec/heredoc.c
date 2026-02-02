/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:15:46 by clados-s          #+#    #+#             */
/*   Updated: 2026/02/02 11:45:10 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*crio um arquivo temporario onde vai ser escrito o heredoc, inicia a linha com
"> ", caso dê uma ctrl +d ele printa  um warning e sai, dps d tudo garanto que
od fd seja fechado e retorne o fd do arquivo temporario*/
int	process_heredoc(char *delimiter)
{
	int		fd;
	char	*line;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("warning: here-document at line 1 delimited by end-of-file \
					(wanted `%s')", delimiter);
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
	close (fd);
	return (open(".heredoc_tmp", O_RDONLY));
}
