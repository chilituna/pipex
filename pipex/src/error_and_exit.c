/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:56:46 by aarponen          #+#    #+#             */
/*   Updated: 2023/11/20 19:53:48 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "pipex.h"

// show the correct usage of the program in standard error stream and exit.
int	ft_arg_error(void)
{
	ft_putstr_fd("Usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 2);
	exit(EXIT_FAILURE);
}

// outfile error
int	ft_error_outfile(char *file, t_pipex *pipex)
{
	ft_putstr_fd("bash: ", 2);
	perror(file);
	ft_cleanup(pipex);
	exit(EXIT_FAILURE);
}

// infile error
void	ft_error_infile(char *file, t_pipex *pipex)
{
	ft_putstr_fd("bash: ", 2);
	perror(file);
	pipex->in_fd = NULL;
}

// command not found error
int	ft_error_path(t_pipex *pipex, char **cmd)
{
	if (!pipex->cmd_path_1)
	{
		ft_putstr_fd(pipex->cmd_arg_1[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (!pipex->cmd_path_2)
	{
		ft_putstr_fd(pipex->cmd_arg_2[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_cleanup(pipex);
		ft_free(cmd);
		exit(127);
	}
	return (0);
}

// show the error message in standard error stream and exit.
int	ft_error(t_pipex *pipex)
{
	perror("Error");
	ft_cleanup(pipex);
	exit(EXIT_FAILURE);
}
