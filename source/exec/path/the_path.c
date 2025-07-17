/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:02:20 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 13:17:46 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*join_path_cmd(const char *dir, const char *cmd)
{
	size_t	len;
	char	*full_path;
	size_t	dir_len;
	size_t	cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	len = dir_len + 1 + cmd_len + 1;
	full_path = malloc(len);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, dir);
	full_path[dir_len] = '/';
	ft_strcpy(full_path + dir_len + 1, cmd);
	return (full_path);
}

static char	*check_dir_for_cmd(const char *dir, const char *cmd)
{
	char	*full_path;

	if (*dir == '\0')
		return (NULL);
	full_path = join_path_cmd(dir, cmd);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static char	*search_in_path(const char *cmd, char *path_env)
{
	char	*path_dup;
	char	*dir;
	char	*full_path;
	char	*saveptr;

	path_dup = ft_strdup(path_env);
	if (!path_dup)
		return (NULL);
	dir = ft_strtok(path_dup, ":", &saveptr);
	while (dir)
	{
		full_path = check_dir_for_cmd(dir, cmd);
		if (full_path)
		{
			free(path_dup);
			return (full_path);
		}
		dir = ft_strtok(NULL, ":", &saveptr);
	}
	free(path_dup);
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char		*path_env;
	struct stat	st;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strcmp(cmd, ".") == 0)
		return (ft_strdup("DOT_COMMAND"));
	if (ft_strcmp(cmd, "..") == 0)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
				return (ft_strdup("IS_DIRECTORY"));
			if (access(cmd, X_OK) == 0)
				return (ft_strdup(cmd));
			return (ft_strdup("PERMISSION_DENIED"));
		}
		return (NULL);
	}
	path_env = get_env_path(envp);
	if (!path_env)
		return (NULL);
	return (search_in_path(cmd, path_env));
}
