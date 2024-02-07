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
	if (pipex->nb_cmd == 1)
	{
		while (i < pipex->nb_cmd)
		{
			if (pipe(pipex->pipes + 2 * i) < 0)
				msg_error("Pipe");
			i++;
		}
	}
	else
	{
		while (i < pipex->nb_cmd - 1)
		{
			if (pipe(pipex->pipes + 2 * i) < 0)
				msg_error("Pipe");
			i++;
		}
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

int	init_struct(t_pipex *pipex, int argc, char *envp[])
{
	pipex->infile = 0;
	if (pipex->infile < 0)
		msg_error("Infile");
	if (!stdin_is_redirected())
	{
		pipex->infile = open("/dev/null", O_RDONLY);
		if (pipex->infile < 0)
			msg_error("Infile");
	}
	pipex->outfile = 1;
	if (pipex->outfile < 0)
		msg_error("Outfile");
	pipex->nb_cmd = argc;
	pipex->nb_pipe = 2 * (pipex->nb_cmd - 1);
	if (pipex->nb_cmd == 1)
		pipex->nb_pipe = 2;
	pipex->pipes = (int *)malloc(sizeof(int) * pipex->nb_pipe);
	if (!pipex->pipes)
		msg_error("Alloc pipes");
	create_pipes(pipex);
	pipex->paths = find_path(envp);
	pipex->cmd_paths = ft_split(pipex->paths, ':');
	pipex->i_pid = -1;
	return (0);
}

int	pipex(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	init_struct(&pipex, argc, envp);
	while (++(pipex.i_pid) < pipex.nb_cmd)
	{
		childs(pipex, argv, envp);
		waitpid(-1, NULL, 0);
	}
	close_pipes(&pipex);
	free_parent(&pipex);
	free(pipex.pipes);
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	int	stdin = dup(0);
	int	stdout = dup(1);

	/*operate_infile_open("test1");
	operate_outfile2_open("test2");
	pipex(argc - 1, argv + 1, envp);
	operate_infile_close(stdin);
	operate_outfile_close(stdout);*/
	//here_doc(argc - 1, argv + 1, envp);
	pipex(argc - 1, argv + 1, envp);
	//operate_outfile_close(stdout);
	return 0;
}
