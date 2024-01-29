/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymostows <ymostows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:50:12 by ymostows          #+#    #+#             */
/*   Updated: 2024/01/15 11:50:12 by ymostows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct s_pipex
{
	int		nb_pipe;
	int		i_pid;
	int		pid;
	int		*pipes;
	int		infile;
	int		outfile;
	char	*paths;
	int		nb_cmd;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}	t_pipex;

void	childs(t_pipex pipex, char *argv[], char *envp[]);
void	free_parent(t_pipex *pipex);
void	free_child(t_pipex *pipex);
void	msg_error(char *error);
int		msg(char *error);

#endif