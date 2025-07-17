/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 23:35:48 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/29 23:38:42 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_target_directory(char **args, char **env)
{
	char	*target;

	if (!args[1] || args[1][0] == '\0')
	{
		target = ms_getenv(env, "HOME", 0);
		if (!target)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
	}
	else if (!ft_strncmp(args[1], "-", 2))
	{
		target = ms_getenv(env, "OLDPWD", 0);
		if (!target)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
			return (NULL);
		}
		else
			ft_putendl_fd(target, STDOUT_FILENO);
	}
	else
		target = args[1];
	return (target);
}

int	update_env_pwd(char ***env, char *oldpwd)
{
	char	*current_dir;

	*env = ms_setenv(*env, "OLDPWD", oldpwd);
	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		current_dir = ft_strdup("");
	*env = ms_setenv(*env, "PWD", current_dir);
	free(current_dir);
	return (0);
}

void	substitute_env_vars(char **args, char **env)
{
	int		i;
	char	*value;
	char	*var_name;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$' && args[i][1] != '\0')
		{
			var_name = args[i] + 1;
			value = ms_getenv(env, var_name, 0);
			if (value)
			{
				free(args[i]);
				args[i] = ft_strdup(value);
			}
			else
			{
				free(args[i]);
				args[i] = ft_strdup("");
			}
		}
		i++;
	}
}

int	ms_cd_wrapper(t_user_info *prompt, t_list *cmd, int *exiter)
{
	t_ast	*node;
	char	**args;
	char	***envp;
	int		ret;

	(void)exiter;
	node = (t_ast *)cmd->content;
	args = node->full_cmd;
	envp = &(prompt->envp);
	substitute_env_vars(args, *envp);
	ret = ms_cd(args, envp);
	if (ret == 0)
	{
		ft_lstclear(&prompt->env, free);
		prompt->env = ms_env_list_init(prompt->envp);
	}
	prompt->last_exit_code = ret;
	return (ret);
}
