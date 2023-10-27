/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikorkut <ikorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:39:48 by egokeri           #+#    #+#             */
/*   Updated: 2023/10/27 15:12:40 by ikorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_dir(char *cmd)
{
	DIR	*dir;

	if (!cmd)
		exit(EXIT_SUCCESS);
	dir = opendir(cmd);
	if (dir && readdir(dir))
	{
		closedir(dir);
		directory_err(cmd);
	}
}

char	*mimi_ret_free(char *mim, char *path)
{
	free(mim);
	return (path);
}

char	*get_path(char *cmd)
{
	char	*path;
	char	**paths;
	char	*new_cmd;

	check_dir(cmd);
	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	paths = g_ms.paths;
	if (!paths)
		command_err(cmd);
	new_cmd = ft_strjoin("/", cmd);
	while (*paths)
	{
		path = ft_strjoin(*paths, new_cmd);
		if (!access(path, F_OK))
			return (mimi_ret_free(new_cmd, path));
		free(path);
		paths++;
	}
	if (ft_strchr(cmd, '/'))
		no_file_err(cmd);
	free(new_cmd);
	return (NULL);
}
