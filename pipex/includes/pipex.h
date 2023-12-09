/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:57:08 by aarponen          #+#    #+#             */
/*   Updated: 2023/11/21 10:20:13 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include "../Libft/libft.h"

typedef struct s_pipex
{
	char	*in_fd;
	char	*out_fd;
	char	*cmd_path_1;
	char	*cmd_path_2;
	char	**cmd_arg_1;
	char	**cmd_arg_2;
	int		exit_status;
}	t_pipex;

//start program, initialize struct, clean up memory
int		main(int argc, char **argv, char **envp);
void	ft_init_pipex(t_pipex *pipex);
void	ft_cleanup(t_pipex *pipex);
void	ft_free(char **arr);

//error handling
int		ft_arg_error(void);
int		ft_error(t_pipex *pipex);
void	ft_error_infile(char *file, t_pipex *pipex);
int		ft_error_outfile(char *file, t_pipex *pipex);
int		ft_error_path(t_pipex *pipex, char **cmd);

//parsing
void	ft_parse_args(char **argv, t_pipex *pipex);
char	**ft_path_arr(char **envp);
void	ft_parse_cmds(t_pipex *pipex, char **envp);
char	*ft_find_cmd_path(char **path_arr, char *cmd, t_pipex *pipex);
char	*ft_get_path(char *tmp_path, char *tmp, t_pipex *pipex);

//executing
void	ft_pipex(t_pipex *pipex, char **envp);
int		ft_check_args(char **argv, t_pipex *pipex);
void	ft_child_1(t_pipex *pipex, int *p_fd, char **envp);
void	ft_child_2(t_pipex *pipex, int *p_fd, char **envp);
void	ft_only_child(t_pipex *pipex, char **envp);

#endif