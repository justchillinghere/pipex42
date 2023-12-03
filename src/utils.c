/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luchitel <luchitel@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:07:33 by luchitel          #+#    #+#             */
/*   Updated: 2023/12/03 23:13:34 by luchitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *find_path(char **envp)
{
	int i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	if (!envp[i])
		print_error("No PATH env provided");
	return (envp[i] + 5);
}

char *get_cmd_path(char *cmd_name, char **envp)
{
	char **paths;
	char *full_path;
	char *path_slash;
	int i;

	i = -1;
	char *path_str = find_path(envp);
	paths = ft_split(path_str, ':');
	while (paths)
	{
		path_slash = ft_strjoin(*paths, "/");
		full_path = ft_strjoin(path_slash, cmd_name);
		free(path_slash);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		paths++;
	}
	while (paths[++i])
		free(paths[i]);
	return (NULL);
}

void execute_cmd(char *cmd_string, char **envp)
{
	char **cmd_args;
	char *cmd_path;
	int i;

	i = -1;
	cmd_args = ft_split(cmd_string, ' ');
	cmd_path = get_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		while (cmd_args[++i])
			free(cmd_args[i]);
		free(cmd_args);
		print_error("Faled to execute command \n");
	}
	if (execve(cmd_path, cmd_args, envp) == -1)
		print_error("Error in command execution\n");
}

void clean_pipes(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}
