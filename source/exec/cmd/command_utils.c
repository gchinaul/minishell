/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:45:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 12:22:41 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static char	*handle_direct_command(const char *cmd)
{
	if (is_executable(cmd))
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*search_command_in_paths(char **paths, const char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_3(paths[i], "/", cmd);
		if (full_path && is_executable(full_path))
		{
			ft_free_matrix(&paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_matrix(&paths);
	return (NULL);
}

char	*find_command_in_path(const char *cmd, char **env)
{
	char	*path_env;
	char	**paths;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (handle_direct_command(cmd));
	path_env = get_env_var("PATH", env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	return (search_command_in_paths(paths, cmd));
}
