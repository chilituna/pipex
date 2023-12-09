/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:44:25 by aarponen          #+#    #+#             */
/*   Updated: 2023/11/21 11:19:13 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

//free the memory allocated for the struct and its members.
void	ft_cleanup(t_pipex *pipex)
{
	if (pipex->cmd_arg_1)
		ft_free(pipex->cmd_arg_1);
	if (pipex->cmd_arg_2)
		ft_free(pipex->cmd_arg_2);
	if (pipex->cmd_path_1)
		free(pipex->cmd_path_1);
	if (pipex->cmd_path_2)
		free(pipex->cmd_path_2);
	if (pipex->in_fd)
		free(pipex->in_fd);
	if (pipex->out_fd)
		free(pipex->out_fd);
}

//initialize the struct and its members.
void	ft_init_pipex(t_pipex *pipex)
{
	pipex->in_fd = NULL;
	pipex->out_fd = NULL;
	pipex->cmd_path_1 = NULL;
	pipex->cmd_path_2 = NULL;
	pipex->cmd_arg_1 = NULL;
	pipex->cmd_arg_2 = NULL;
	pipex->exit_status = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		ft_arg_error();
	ft_init_pipex(&pipex);
	ft_check_args(argv, &pipex);
	ft_parse_args(argv, &pipex);
	ft_parse_cmds(&pipex, envp);
	if (pipex.cmd_path_1 == NULL || pipex.in_fd == NULL)
		ft_only_child(&pipex, envp);
	else
		ft_pipex(&pipex, envp);
	ft_cleanup(&pipex);
	return (pipex.exit_status);
}
