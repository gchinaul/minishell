/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:09:40 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/29 23:51:18 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_flag_n(const char *arg)
{
	int	i;

	i = 1;
	if (!arg || arg[0] != '-' || !arg[1])
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	skip_n_flags(char **argv, int *newline)
{
	int	i;

	i = 1;
	*newline = 1;
	while (argv && argv[i] && is_flag_n(argv[i]))
	{
		*newline = 0;
		i++;
	}
	return (i);
}

static void	print_echo_args(char **argv, int start)
{
	int		first_arg;
	ssize_t	ret;

	first_arg = 1;
	while (argv && argv[start])
	{
		if (!first_arg)
		{
			ret = write(STDOUT_FILENO, " ", 1);
			(void)ret;
		}
		ret = write(STDOUT_FILENO, argv[start], ft_strlen(argv[start]));
		(void)ret;
		first_arg = 0;
		start++;
	}
}

int	ms_echo(t_list *cmd)
{
	char	**argv;
	t_ast	*node;
	int		newline;
	int		start;
	ssize_t	ret;

	node = cmd->content;
	argv = node->full_cmd;
	if (!argv || !argv[0])
	{
		ret = write(STDOUT_FILENO, "\n", 1);
		(void)ret;
		return (0);
	}
	start = skip_n_flags(argv, &newline);
	print_echo_args(argv, start);
	if (newline)
	{
		ret = write(STDOUT_FILENO, "\n", 1);
		(void)ret;
	}
	return (0);
}
