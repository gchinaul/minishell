/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_war.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:58:58 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 00:31:57 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_export_arg(char ***envp, const char *arg)
{
	char	**new_env;
	int		error_code;

	if (!is_valid_identifier_export(arg))
	{
		print_export_error(arg);
		return (1);
	}
	new_env = ms_env_export(*envp, arg, &error_code);
	if (error_code != 0)
		return (1);
	if (new_env)
		*envp = new_env;
	return (0);
}

static void	update_env_list(t_user_info *prompt)
{
	ft_lstclear(&prompt->env, free);
	prompt->env = ms_env_list_init(prompt->envp);
}

static int	is_export_list(char **args)
{
	return (!args[1]);
}

static int	handle_export_list(char ***envp, int *error_code,
		t_user_info *prompt)
{
	ms_env_export(*envp, NULL, error_code);
	prompt->last_exit_code = *error_code;
	return (*error_code);
}

int	ms_env_export_wrapper(t_user_info *prompt, t_list *cmd, int *error_code)
{
	t_ast	*node;
	char	**args;
	char	***envp;
	int		overall_error;

	node = (t_ast *)cmd->content;
	args = node->full_cmd;
	envp = &(prompt->envp);
	if (is_export_list(args))
		return (handle_export_list(envp, error_code, prompt));
	overall_error = handle_export_args_2(envp, args);
	update_env_list(prompt);
	prompt->last_exit_code = overall_error;
	return (overall_error);
}
