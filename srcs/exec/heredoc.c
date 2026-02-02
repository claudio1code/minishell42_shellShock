/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:15:46 by clados-s          #+#    #+#             */
/*   Updated: 2026/02/02 14:29:34 by clados-s         ###   ########.fr       */
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
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("warning: here-document at line 1 delimited by", 2);
			ft_putstr_fd("end-of-file (wanted `", 2);
			ft_putstr_fd(delimiter, 2);
			ft_putstr_fd("')\n", 2);
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

int	process_heredoc(char *delimiter)
{
	int		fd;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	loop_heredoc(fd, delimiter);
	close (fd);
	if (g_sig == SIGINT)
		return (-1);
	return (open(".heredoc_tmp", O_RDONLY));
}
