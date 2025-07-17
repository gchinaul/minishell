/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:40:21 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/29 23:33:45 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_exit_status(int ac, char **argv, int last_code, int *is_valid)
{
	long long	code;

	*is_valid = 1;
	if (ac == 1)
		return (last_code);
	if (!is_numeric(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	if (ac > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		*is_valid = 0;
		return (1);
	}
	code = ft_atol(argv[1]);
	return ((unsigned char)code);
}

int	ms_exit_wrapper(t_user_info *prompt, t_list *cmd, int *exiter)
{
	t_ast	*node;
	char	**args;
	int		ac;
	int		is_valid_exit;

	node = (t_ast *)cmd->content;
	args = node->full_cmd;
	ac = 0;
	while (args && args[ac])
		ac++;
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		ft_putstr_fd("exit\n", STDERR_FILENO);
	prompt->last_exit_code = parse_exit_status(ac, args, prompt->last_exit_code,
			&is_valid_exit);
	if (is_valid_exit)
		*exiter = 1;
	else
		*exiter = 0;
	return (prompt->last_exit_code);
}
