/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_war.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 00:13:59 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 00:20:29 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(const char *key)
{
	int	i;

	if (!key || !*key)
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	update_env_list(t_user_info *prompt, char **new_env)
{
	*(&prompt->envp) = new_env;
	ft_lstclear(&prompt->env, free);
	prompt->env = ms_env_list_init(new_env);
}

static void	handle_unset_args(char ***envp, char **args, t_user_info *prompt)
{
	int		i;
	char	**new_env;

	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]))
		{
			new_env = ms_unsetenv(*envp, args[i]);
			if (new_env)
				update_env_list(prompt, new_env);
		}
		i++;
	}
}

int	ms_unsetenv_wrapper(t_user_info *prompt, t_list *cmd, int *exiter)
{
	t_ast	*node;
	char	**args;
	char	***envp;
	int		exit_code;

	node = (t_ast *)cmd->content;
	args = node->full_cmd;
	envp = &(prompt->envp);
	exit_code = 0;
	(void)exiter;
	if (!args[1])
	{
		prompt->last_exit_code = 0;
		return (0);
	}
	handle_unset_args(envp, args, prompt);
	prompt->last_exit_code = exit_code;
	return (exit_code);
}
