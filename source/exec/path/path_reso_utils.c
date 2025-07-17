/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_reso_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:13:26 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 12:16:04 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_exists_path(const char *path)
{
	return (access(path, F_OK) == 0);
}

int	is_executable_file_path(const char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (0);
	return (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR));
}

char	*build_full_path_path(const char *dir, const char *cmd)
{
	char	*path;
	int		dir_len;
	int		cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	path = malloc(dir_len + cmd_len + 2);
	if (!path)
		return (NULL);
	ft_strcpy(path, dir);
	if (dir_len > 0 && path[dir_len - 1] != '/')
		ft_strcat(path, "/");
	ft_strcat(path, cmd);
	return (path);
}
