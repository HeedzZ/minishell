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
#include "libft/libft.h"

static char	*infile_manager_read(char *buffer, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line != 0)
	{
		//printf("line+1\n");
		if (!line)
			return (0);
		buffer = ft_strjoin_gnl(buffer, line);
		//printf("%s\n", buffer);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (buffer);
}

static int	infile_manager_write(char *buffer)
{
	int		temp_file;
	int		i;

	temp_file = open("infile_manager", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (temp_file < 0)
		msg_error("fd :infile_manager");
	i = 0;
	while (buffer[i])
	{
		write(temp_file, &buffer[i], 1);
		i++;
	}
	close(temp_file);
	return (0);
}

static int	outfile_manager_write(char *buffer, int fd)
{
	int		i;

	i = 0;
	while (buffer[i])
	{
		write(fd, &buffer[i], 1);
		i++;
	}
	close(fd);
	return (0);
}

int	infile_manager(t_list *file_lst)
{
	char	*buffer;
	int		file_fd;

	if (file_lst->next == 0)
		return (operate_infile_open_fd(file_lst->content), 0);
	buffer = malloc(sizeof(char));
	if (!buffer)
		return (1);
	buffer[0] = '\0';
	while (file_lst != 0)
	{
		file_fd = file_lst->content;
		buffer = infile_manager_read(buffer, file_fd);
		if (!buffer)
			return (1);
		close(file_fd);
		file_lst = file_lst->next;
	}
	infile_manager_write(buffer);
	free(buffer);
	operate_infile_open("infile_manager");
	return(0);
}

int	outfile_manager(t_list *file_lst) /*cpy le contenu du premier elem de la list dans tt les autres*/
{
	char	*buffer;
	int		file_fd;

	buffer = malloc(sizeof(char));
	if (!buffer)
		return (0);
	buffer[0] = '\0';
	file_fd = file_lst->content;
	buffer = infile_manager_read(buffer, file_fd);
	if (!buffer)
		return (0);
	close(file_fd);
	file_lst = file_lst->next;
	while (file_lst != 0)
	{
		outfile_manager_write(buffer, file_lst->content);
		file_lst = file_lst->next;
	}
	free(buffer);
	//operate_outfile_open("outfile_manager");
	return(1);
}

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

int	operate_infile_open_fd(int fd)
{
	dup2(fd, 0);
	return (0);
}

int	operate_infile_close(int stdin)
{
	close(0);
	dup2(stdin, 0);
	return (0);
}

int	operate_outfile_open(int fd)
{
	dup2(fd, 1);
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
	close(1);
	dup2(stdout, 1);
	return (0);
}