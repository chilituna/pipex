/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:52:28 by aarponen          #+#    #+#             */
/*   Updated: 2023/11/21 11:18:13 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//checks that the files exist and that the user has the right to read and write
//if the output file exists and user cannot write: error and exit
//if the output file exists and user can write: overwrite the file
//if the output file does not exist, create it
//if the input file does not exist or user cannot read: error 
int	ft_check_args(char **argv, t_pipex *pipex)
{
	int		fd;

	if (access((argv[4]), F_OK) == 0 && access((argv[4]), W_OK) == -1)
		ft_error_outfile(argv[4], pipex);
	if (access((argv[4]), F_OK) == 0)
	{
		fd = open(argv[4], O_TRUNC);
		if (fd == -1)
			ft_error(pipex);
		close(fd);
	}
	else
	{
		fd = open(argv[4], O_CREAT, 0664);
		close(fd);
	}
	pipex->out_fd = ft_strdup(argv[4]);
	if (access(argv[1], R_OK) == -1)
		ft_error_infile(argv[1], pipex);
	else
		pipex->in_fd = ft_strdup(argv[1]);
	return (0);
}

//child1_process:
//use dup2 to manipulate stdin and stdout:
//input: the input file
//output: the write end of the pipe
//execute the command with the input file as input
void	ft_child_1(t_pipex *pipex, int *p_fd, char **envp)
{
	int		fd;

	close(p_fd[0]);
	fd = open(pipex->in_fd, O_RDONLY);
	if (fd == -1)
		ft_error(pipex);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	if (execve(pipex->cmd_path_1, pipex->cmd_arg_1, envp) == -1)
		ft_error(pipex);
}

//child2_process:
//use dup2 to manipulate stdin and stdout:
//execute the command with the read end of the pipe as input
//redirect the output to the output file
void	ft_child_2(t_pipex *pipex, int *p_fd, char **envp)
{
	int		fd;

	close(p_fd[1]);
	fd = open(pipex->out_fd, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		ft_error(pipex);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(p_fd[0], STDIN_FILENO);
	close(p_fd[0]);
	if (execve(pipex->cmd_path_2, pipex->cmd_arg_2, envp) == -1)
		ft_error(pipex);
}

//child3_process:
//to be excecuted if the input file or the first command are wrong
//no pipe needed: 
//as input, use /dev/null
//redirect the output to the output file
void	ft_only_child(t_pipex *pipex, char **envp)
{
	int		fd;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		ft_error(pipex);
	if (pid == 0)
	{
		fd = open("/dev/null", O_RDONLY);
		if (fd == -1)
			ft_error(pipex);
		dup2(fd, STDIN_FILENO);
		close(fd);
		fd = open(pipex->out_fd, O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
			ft_error(pipex);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		if (execve(pipex->cmd_path_2, pipex->cmd_arg_2, envp) == -1)
			ft_error(pipex);
	}
	waitpid(pid, &status, 0);
	pipex->exit_status = WEXITSTATUS(status);
}

//send the output of the 1st command to the input of the 2nd command with pipe
//use fork to create 2 child processes
//get the exit status from last command
void	ft_pipex(t_pipex *pipex, char **envp)
{
	int		p_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(p_fd) == -1)
		ft_error(pipex);
	pid1 = fork();
	if (pid1 == -1)
		ft_error(pipex);
	if (pid1 == 0)
		ft_child_1(pipex, p_fd, envp);
	pid2 = fork();
	if (pid2 == -1)
		ft_error(pipex);
	if (pid2 == 0)
		ft_child_2(pipex, p_fd, envp);
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	pipex->exit_status = WEXITSTATUS(status);
}
