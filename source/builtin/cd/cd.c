/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:54:49 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/29 23:38:58 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_cd_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	if (count > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

static char	*get_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_strdup("");
	return (oldpwd);
}

static int	change_directory(const char *target)
{
	if (chdir(target) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(target, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	ms_cd(char **args, char ***env)
{
	char	*oldpwd;
	char	*target;

	if (check_cd_args(args))
		return (1);
	oldpwd = get_oldpwd();
	target = get_target_directory(args, *env);
	if (!target)
	{
		free(oldpwd);
		return (1);
	}
	if (change_directory(target))
	{
		free(oldpwd);
		return (1);
	}
	update_env_pwd(env, oldpwd);
	free(oldpwd);
	return (0);
}
