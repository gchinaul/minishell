/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:46:40 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/21 21:01:47 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	ft_putendl_fd(buffer, 1);
	free(buffer);
	return (0);
}

int	ms_pwd_wrapper(t_user_info *prompt, t_list *cmd, int *exiter)
{
	(void)prompt;
	(void)cmd;
	(void)exiter;
	return (ms_pwd());
}
