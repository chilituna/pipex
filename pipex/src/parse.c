/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:47:20 by aarponen          #+#    #+#             */
/*   Updated: 2023/12/09 13:30:30 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//parse the commands and store them in an array
//make sure the arguments are not empty
void	ft_parse_args(char **argv, t_pipex *pipex)
{
	char	**cmd_arr;

	if (ft_strlen(argv[2]) == 0 || ft_strlen(argv[3]) == 0)
		ft_arg_error();
	cmd_arr = ft_split(argv[2], ' ');
	pipex->cmd_arg_1 = cmd_arr;
	cmd_arr = ft_split(argv[3], ' ');
	pipex->cmd_arg_2 = cmd_arr;
}

//extract the paths from envp
//split the paths into an array
char	**ft_path_arr(char **envp)
{
	int		i;
	char	*path;
	char	**path_arr;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i] + 5;
		i++;
	}
	path_arr = ft_split(path, ':');
	return (path_arr);
}

char	*ft_get_path(char *tmp_path, char *tmp, t_pipex *pipex)
{
	char	*cmd_path;
	int		count_chars;

	count_chars = ft_strlen(tmp_path);
	cmd_path = (char *)malloc(sizeof(char) * (count_chars + 1));
	if (!cmd_path)
	{
		free(tmp);
		free(tmp_path);
		ft_error(pipex);
	}
	ft_strlcpy(cmd_path, tmp_path, count_chars + 1);
	free(tmp);
	free(tmp_path);
	return (cmd_path);
}

//check if the command is an absolute path, else:
//concatenate the path with the /command
//check if the command exists with access()
//if the command exists, return the path
//if the command does not exist, return NULL
char	*ft_find_cmd_path(char **path_arr, char *cmd, t_pipex *pipex)
{
	int		i;
	char	*tmp;
	char	*tmp_path;

	i = 0;
	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	while (path_arr[i])
	{
		tmp = ft_strjoin(path_arr[i], "/");
		tmp_path = ft_strjoin(tmp, cmd);
		if (access(tmp_path, F_OK) == 0)
			return (ft_get_path(tmp_path, tmp, pipex));
		free(tmp);
		free(tmp_path);
		i++;
	}
	return (NULL);
}

//find the correct path using envp and store it in the struct
void	ft_parse_cmds(t_pipex *pipex, char **envp)
{
	char	**path_arr;

	path_arr = ft_path_arr(envp);
	pipex->cmd_path_1 = ft_find_cmd_path(path_arr, pipex->cmd_arg_1[0], pipex);
	pipex->cmd_path_2 = ft_find_cmd_path(path_arr, pipex->cmd_arg_2[0], pipex);
	if (!pipex->cmd_path_1 || !pipex->cmd_path_2)
		ft_error_path(pipex, path_arr);
	ft_free(path_arr);
}
