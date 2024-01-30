/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymostows <ymostows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:50:22 by ymostows          #+#    #+#             */
/*   Updated: 2024/01/15 11:50:22 by ymostows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*temp;
	char	*command;

	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		command = ft_strjoin(temp, cmd);
		free(temp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

static void	double_dup2(int zero, int one)
{
	dup2(zero, 0);
	dup2(one, 1);
}

void	childs(t_pipex pipex, char *argv[], char *envp[])
{
	pipex.pid = fork();
	if (!pipex.pid)
	{
		if (pipex.i_pid == 0)
			double_dup2(pipex.infile, pipex.pipes[1]);
		else if (pipex.i_pid == pipex.nb_cmd - 1)
			double_dup2(pipex.pipes[2 * pipex.i_pid - 2], pipex.outfile);
		else
			double_dup2(pipex.pipes[2 * pipex.i_pid - 2], pipex.pipes[2 * pipex.i_pid + 1]);
		pipex.cmd_args = ft_split(argv[pipex.i_pid + 2], ' ');
		pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
		if (!pipex.cmd)
		{
			free_child(&pipex);
			msg("Command not found\n");
			exit(1);
		}
		execve(pipex.cmd, pipex.cmd_args, envp);
	}
}

