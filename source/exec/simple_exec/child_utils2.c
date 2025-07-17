/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:26:55 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 13:29:38 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_sim(int code, char *msg, char *to_free, t_user_info *user)
{
	ssize_t	ret;

	if (msg)
	{
		ret = write(STDERR_FILENO, msg, ft_strlen(msg));
		(void)ret;
	}
	if (to_free)
		free(to_free);
	cleanup_child_memory_sim(user);
	exit(code);
}

void	print_and_exit_perm(const char *cmd_name, t_user_info *user)
{
	ssize_t	ret;

	ret = write(STDERR_FILENO, "bash: ligne 1: ", 15);
	(void)ret;
	ret = write(STDERR_FILENO, cmd_name, ft_strlen(cmd_name));
	(void)ret;
	ret = write(STDERR_FILENO, ": Permission denied\n", 20);
	(void)ret;
	exit_sim(126, NULL, NULL, user);
}
