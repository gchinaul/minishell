/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:29:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 12:53:55 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env(char **env)
{
	int		i;
	ssize_t	ret;

	if (!env)
	{
		ret = write(STDERR_FILENO, "env: environment is NULL\n", 26);
		(void)ret;
		return (1);
	}
	i = 0;
	while (env[i])
	{
		if (env[i][0] != '\0')
		{
			ret = write(STDOUT_FILENO, env[i], ft_strlen(env[i]));
			(void)ret;
			ret = write(STDOUT_FILENO, "\n", 1);
			(void)ret;
		}
		i++;
	}
	return (0);
}

int	ms_env_wrapper(t_user_info *prompt, t_list *cmd, int *exiter)
{
	t_ast	*node;
	char	**args;
	char	**envp;
	ssize_t	ret;

	(void)exiter;
	node = (t_ast *)cmd->content;
	args = node->full_cmd;
	envp = prompt->envp;
	if (args[1] != NULL)
	{
		ret = write(STDERR_FILENO, "env: '", 6);
		(void)ret;
		ret = write(STDERR_FILENO, args[1], ft_strlen(args[1]));
		(void)ret;
		ret = write(STDERR_FILENO, "': No such file or directory\n", 29);
		(void)ret;
		return (127);
	}
	return (ms_env(envp));
}
