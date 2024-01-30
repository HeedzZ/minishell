/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymostows <ymostows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:49:31 by ymostows          #+#    #+#             */
/*   Updated: 2024/01/15 11:49:31 by ymostows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmd - 1)
	{
		if (pipe(pipex->pipes + 2 * i) < 0)
			msg_error("Pipe");
		i++;
	}
}

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_pipe)
	{
		close(pipex->pipes[i]);
		i++;
	}
}

static int	stdin_is_redirected()
{
	struct stat statbuf;
	if (fstat(0, &statbuf) < 0)
		msg_error("fstat");
	return (S_ISREG(statbuf.st_mode));
}

int	pipex(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	pipex.infile = 0;
	if (pipex.infile < 0)
		msg_error("Infile");
	if (!stdin_is_redirected())
	{
		pipex.infile = open("/dev/null", O_RDONLY);
		if (pipex.infile < 0)
			msg_error("Infile");
	}
	pipex.outfile = 1;
	if (pipex.outfile < 0)
		msg_error("Outfile");
	pipex.nb_cmd = argc - 3;
	pipex.nb_pipe = 2 * (pipex.nb_cmd - 1);
	pipex.pipes = (int *)malloc(sizeof(int) * pipex.nb_pipe);
	if (!pipex.pipes)
		msg_error("Alloc pipes");
	create_pipes(&pipex);
	pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.i_pid = -1;
	while (++(pipex.i_pid) < pipex.nb_cmd)
		childs(pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(-1, NULL, 0);
	free_parent(&pipex);
	return (0);
}

int	operat_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		msg_error("Open");
	dup2(fd, 0);
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	/*int	fds[2];

	fds[0] = open(argv[1], O_RDONLY);
	fds[1] = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	dup2(fds[0], 0);
	dup2(fds[1], 1);*/
	operat_infile(file1);
	operat_infile(file2);
	operat_infile(file3);
	char b;
	while (read(0, &b, 1))
    	write(1, &b, 1);
	//pipex(argc, argv, envp);
	/*close(fds[0]);
	close(fds[1]);*/
	return 0;
}