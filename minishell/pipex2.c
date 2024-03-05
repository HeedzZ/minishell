/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:30:33 by marvin            #+#    #+#             */
/*   Updated: 2024/03/04 13:30:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

#define WRITE_FLAGS O_TRUNC | O_CREAT | O_WRONLY
# define IN_HEREDOC 1
# define OUT_APPEND 2

typedef struct s_command {
    char    	**command;
    int         fd_in;
    int         fd_out;
}    t_command;

int	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (1);
}

static char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

int	cmd_exec(char **arr_cmd, char **envp)
{
	char	**paths;
	char	*cmd;

	paths = ft_split(find_path(envp), ':');
	cmd = get_cmd(paths, arr_cmd[0]);
	if (!cmd)
		return (ft_free_array(paths));
	ft_free_array(paths);
	return (execve(cmd, arr_cmd, envp));
}

int    execute_command(t_command *cmd, char **envp)
{
    int		out;

    //Execute la commande apres redirections
	dup2(cmd->fd_out, 1);
	dup2(cmd->fd_in, 0);
    out = cmd_exec(cmd->command, envp);
    close(cmd->fd_in);
    close(cmd->fd_out);
    return (out);
}

void    pipe_exe(int cmdc, t_command *cmds, char **envp)
{
    int    pid;
    int    fd_pipe[2];

    //Preparation du pipe
    if (cmdc < 2)
        return ;
    if (pipe(fd_pipe) == -1)
        perror("pipex: pipe");
    pid = fork();
    if (pid == -1)
        perror("pipex: fork");
    //Execution du pipe
    else if (pid == 0)
    {
        //Setup et execute la premiere commande du tableau
        if (cmds[0].fd_out == 1)
		    cmds[0].fd_out = fd_pipe[1];
        close(fd_pipe[0]);
        execute_command(&cmds[0], envp);
    }
    else
    {
        //Setup la 2e commande et l'execute ou s'appelle recursivement
		if (cmds[1].fd_in == 0)
            cmds[1].fd_in = fd_pipe[0];
        close(fd_pipe[1]);
        if (cmdc == 2)
            execute_command(&cmds[1], envp);
        else
            pipe_exe(cmdc - 1, cmds + 1, envp);
    }
}


int    main(int argc, char **argv, char **envp)
{
    t_command    *cmds;
    int            k;

    cmds = malloc(sizeof(t_command) * (argc - 1));
    if (!cmds)
        exit(EXIT_FAILURE);
    
    //Preparations des commandes
    k = -1;
    while (++k < argc - 1)
	{
        cmds[k].command = ft_split(argv[k + 1], ' ');
        cmds[k].fd_in = 0;
        cmds[k].fd_out = 1;
	}
    //Executions des commandes
    pipe_exe(argc - 1, cmds, envp);

    //Fermeture des fichiers d'entrée et sortie
    wait(0);
    return (0);
}