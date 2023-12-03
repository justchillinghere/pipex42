/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luchitel <luchitel@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:48:44 by luchitel          #+#    #+#             */
/*   Updated: 2023/12/03 23:13:02 by luchitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void exec_child_1(int *pipe_fd, char **argv, char **envp)
{
	int file_fd;

	close(pipe_fd[0]);
	file_fd = open(argv[1], O_RDONLY);
	if (file_fd < 0)
		print_error("Cannot open input file\n");
	dup2(file_fd, STDIN_FILENO);
	close(file_fd); // Close the file descriptor after dup2
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]); // Close the pipe end after dup2
	execute_cmd(argv[2], envp);
}

void exec_child_2(int *pipe_fd, char **argv, char **envp)
{
	int file_fd;

	close(pipe_fd[1]);
	file_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fd < 0)
		print_error("Cannot open output file\n");
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	execute_cmd(argv[3], envp);
}

int main(int argc, char **argv, char **envp)
{
	int fd[2];
	int pid1;
	int pid2;

	if (argc != 5)
		print_error("Invalid number of arguments\n");
	if (pipe(fd) == -1)
		print_error("Error in pipe creation");
	pid1 = fork();
	if (pid1 < 0)
		print_error("Error in forking");
	if (pid1 == 0)
		exec_child_1(fd, argv, envp);
	pid2 = fork();
	if (pid2 < 0)
		print_error("Error in forking");
	if (pid2 == 0)
		exec_child_2(fd, argv, envp);
	clean_pipes(fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
