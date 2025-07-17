/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:46:15 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 13:26:36 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_and_exit_dir(const char *cmd_name, t_user_info *user)
{
	ssize_t	ret;

	ret = write(STDERR_FILENO, "bash: ligne 1: ", 15);
	(void)ret;
	ret = write(STDERR_FILENO, cmd_name, ft_strlen(cmd_name));
	(void)ret;
	ret = write(STDERR_FILENO, " : est un dossier\n", 18);
	(void)ret;
	exit_sim(126, NULL, NULL, user);
}

void	handle_dot_command(const char *cmd_path, const char *cmd_name,
		t_user_info *user)
{
	free((char *)cmd_path);
	free((char *)cmd_name);
	exit_sim(2, "bash: ligne 1: .: filename argument required\n" ".: usage: \
		. filename [arguments]\n", NULL, user);
}

void	handle_permission_denied(const char *cmd_path, const char *cmd_name,
		t_user_info *user)
{
	ssize_t	ret;

	ret = write(STDERR_FILENO, "bash: ligne 1: ", 15);
	(void)ret;
	ret = write(STDERR_FILENO, cmd_name, ft_strlen(cmd_name));
	(void)ret;
	ret = write(STDERR_FILENO, ": Permission denied\n", 20);
	(void)ret;
	free((char *)cmd_path);
	free((char *)cmd_name);
	exit_sim(126, NULL, NULL, user);
}

void	handle_is_directory(const char *cmd_path, const char *cmd_name,
		t_user_info *user)
{
	ssize_t	ret;

	ret = write(STDERR_FILENO, "bash: ligne 1: ", 15);
	(void)ret;
	ret = write(STDERR_FILENO, cmd_name, ft_strlen(cmd_name));
	(void)ret;
	ret = write(STDERR_FILENO, " : est un dossier\n", 18);
	(void)ret;
	free((char *)cmd_path);
	free((char *)cmd_name);
	exit_sim(126, NULL, NULL, user);
}

void	handle_cmd_path_errors_s(const char *cmd_path, const char *cmd_name,
		t_user_info *user)
{
	if (ft_strcmp(cmd_path, "DOT_COMMAND") == 0)
		handle_dot_command(cmd_path, cmd_name, user);
	if (ft_strcmp(cmd_path, "PERMISSION_DENIED") == 0)
		handle_permission_denied(cmd_path, cmd_name, user);
	if (ft_strcmp(cmd_path, "IS_DIRECTORY") == 0)
		handle_is_directory(cmd_path, cmd_name, user);
}
