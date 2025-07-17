/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:30:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/28 01:08:30 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_command_not_found(const char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	print_permission_denied(const char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)cmd, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}

void	print_no_such_file(const char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
