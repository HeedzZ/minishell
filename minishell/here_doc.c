/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:30:18 by marvin            #+#    #+#             */
/*   Updated: 2024/02/06 17:30:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	here_doc_write(char *buffer)
{
	int		fd;
	int		i;

	fd = open("/tmp/here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		msg_error("fd");
	i = 0;
	while (buffer[i])
	{
		write(fd, &buffer[i], 1);
		i++;
	}
	return (fd);
}

static char	*here_doc_read(char *buffer, char *marker)
{
	char	*line;
	int		len_line;

	line = readline("heredoc> ");
	if (!line)
		return (0);
	while (ft_strncmp(line, marker, ft_strlen(line)) != 0)
	{
		if (!line)
			return (0);
		if (ft_strncmp(line, marker, ft_strlen(line)) != 0)
		{
			buffer = ft_strjoin_gnl(buffer, line);
			if (!buffer)
				return (0);
		}
		len_line = ft_strlen(line);
		line[len_line] = '\0';
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	return (buffer);
}

int	here_doc(char *marker) /*pipex(argc - 2, argv + 2) pour que ça marche*/
{
	char	*buffer;
	int		fd;

	buffer = malloc(sizeof(char));
	if (!buffer)
		return (0);
	buffer[0] = '\0';
	buffer = here_doc_read(buffer, marker);
	if (!buffer)
		return (0);
	fd = here_doc_write(buffer);
	free(buffer);
	return (fd);
}