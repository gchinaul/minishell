/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:00:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 12:17:51 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>
#include <unistd.h>

static char	*handle_direct_path(const char *cmd)
{
	if (file_exists_path(cmd))
	{
		if (is_directory(cmd))
		{
			print_permission_denied(cmd);
			return (NULL);
		}
		if (is_executable_file_path(cmd))
			return (ft_strdup(cmd));
		print_permission_denied(cmd);
		return (NULL);
	}
	print_no_such_file(cmd);
	return (NULL);
}

static char	*find_executable_in_paths(char **paths, const char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = build_full_path_path(paths[i], cmd);
		if (full_path && is_executable_file_path(full_path))
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	*search_in_path(const char *cmd, char **env)
{
	char	*path_env;
	char	**paths;
	char	*result;

	path_env = get_env_var("PATH", env);
	if (!path_env)
	{
		print_command_not_found(cmd);
		return (NULL);
	}
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	result = find_executable_in_paths(paths, cmd);
	ft_free_matrix(&paths);
	if (result)
		return (result);
	print_command_not_found(cmd);
	return (NULL);
}

char	*resolve_command_path(const char *cmd, char **env)
{
	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (handle_direct_path(cmd));
	return (search_in_path(cmd, env));
}
