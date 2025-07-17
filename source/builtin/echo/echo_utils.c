/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:00:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/29 23:43:43 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_option(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || !arg[1])
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo_builtin_improved(char **args)
{
	int	i;
	int	newline;
	int	first_arg;

	newline = 1;
	i = 1;
	while (args[i] && is_n_option(args[i]))
	{
		newline = 0;
		i++;
	}
	first_arg = 1;
	while (args[i])
	{
		if (!first_arg)
			printf(" ");
		printf("%s", args[i]);
		first_arg = 0;
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

int	ms_echo_wrapper(t_user_info *prompt, t_list *cmd, int *exiter)
{
	(void)exiter;
	prompt->last_exit_code = ms_echo(cmd);
	return (prompt->last_exit_code);
}
