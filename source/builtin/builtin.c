/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:57:54 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/29 23:30:41 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_builtin	*get_builtins(void)
{
	static t_builtin	builtins[] = {
	{"cd", ms_cd_wrapper}, {"export", ms_env_export_wrapper},
	{"unset", ms_unsetenv_wrapper}, {"env", ms_env_wrapper},
	{"exit", ms_exit_wrapper}, {"echo", ms_echo_wrapper},
	{"pwd", ms_pwd_wrapper}, {NULL, NULL}};

	return (builtins);
}

static int	find_builtin_index(char *cmd_name, t_builtin *builtins)
{
	int	i;

	i = 0;
	while (builtins[i].name != NULL)
	{
		if (!ft_strncmp(cmd_name, builtins[i].name, ft_strlen(builtins[i].name)
				+ 1))
			return (i);
		i++;
	}
	return (-1);
}

static void	update_underscore(t_user_info *prompt, t_ast *node)
{
	int	j;

	if (node && node->full_cmd)
	{
		j = 0;
		while (node->full_cmd[j])
			j++;
		if (j > 0)
			prompt->envp = ms_setenv(prompt->envp, "_", node->full_cmd[j - 1]);
	}
}

static int	execute_builtin(t_user_info *prompt, t_list *cmd, int *exiter)
{
	t_ast		*node;
	char		**args;
	t_builtin	*builtins;
	int			idx;

	node = (t_ast *)cmd->content;
	args = node->full_cmd;
	builtins = get_builtins();
	idx = find_builtin_index(args[0], builtins);
	if (idx < 0)
		return (127);
	prompt->last_exit_code = builtins[idx].func(prompt, cmd, exiter);
	update_underscore(prompt, node);
	return (prompt->last_exit_code);
}

int	ms_builtin(t_user_info *prompt, t_list *cmd, int *exiter)
{
	t_ast	*node;
	char	**args;

	if (!cmd || !cmd->content)
		return (0);
	node = (t_ast *)cmd->content;
	args = node->full_cmd;
	if (!args || !args[0])
		return (0);
	return (execute_builtin(prompt, cmd, exiter));
}
