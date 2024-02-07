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

static int	here_doc_write(char *buffer, int argc, char *argv[], char *envp[])
{
	int		fd;
	int		i;
	int	stdin = dup(0);

	fd = open("/tmp/here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		msg_error("fd");
	i = 0;
	while (buffer[i])
	{
		write(fd, &buffer[i], 1);
		i++;
	}
	operate_infile_open("/tmp/here_doc");
	pipex(argc - 1, argv + 1, envp);
	operate_infile_close(stdin);
	return (0);
}

static char	*here_doc_read(char *buffer, char *argv[])
{
	char	*line;
	int		len_line;

	write(0, "heredoc> ", 9);
	line = get_next_line(0);
	if (!line)
		return (0);
	while (ft_strcmp(line, argv[0]) != 0)
	{
		write(0, "heredoc> ", 9);
		free(line);
		line = get_next_line(0);
		if (!line)
			return (0);
		if (ft_strcmp(line, argv[0]) != 0)
		{
			buffer = ft_strjoin_gnl(buffer, line);
			if (!buffer)
				return (0);
		}
		len_line = ft_strlen(line);
		line[len_line] = '\0';
	}
	free(line);
	return (buffer);
}

int	here_doc(int argc, char *argv[], char *envp[]) // ex arg : "marquer cmd"
{
	char	*buffer;

	buffer = malloc(sizeof(char));
	if (!buffer)
		return (0);
	buffer[0] = '\0';
	buffer = here_doc_read(buffer, argv);
	if (!buffer)
		return (0);
	here_doc_write(buffer, argc, argv, envp);
	free(buffer);
	return (1);
}