/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:36:10 by marvin            #+#    #+#             */
/*   Updated: 2024/02/06 17:36:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	operate_infile_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		msg_error("fd");

	dup2(fd, 0);
	close(fd);
	return (0);
}

int	operate_infile_close(int stdin)
{
	dup2(stdin, 0);
	return (0);
}

int	operate_outfile_open(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		msg_error("fd");

	dup2(fd, 1);
	close(fd);
	return (0);
}

int	operate_outfile_append_open(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
		msg_error("fd");

	dup2(fd, 1);
	close(fd);
	return (0);
}

int	operate_outfile_close(int stdout)
{
	dup2(stdout, 1);
	return (0);
}