/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:42:45 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/29 23:18:22 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**copy_env(char **envp)
{
	int		len;
	char	**copy;
	int		i;

	len = ft_matrixlen(envp);
	copy = malloc(sizeof(char *) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			ft_free_matrix(&copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = 0;
	return (copy);
}

static char	**handle_shlvl(char **env)
{
	char	*shlvl_str;
	int		shlvl;

	shlvl_str = get_env_var("SHLVL", env);
	if (shlvl_str)
	{
		shlvl = ft_atol(shlvl_str) + 1;
		free(shlvl_str);
	}
	else
		shlvl = 1;
	shlvl_str = ft_itoa(shlvl);
	if (shlvl_str)
	{
		env = ms_setenv(env, "SHLVL", shlvl_str);
		free(shlvl_str);
	}
	return (env);
}

static char	**init_underscore(char **env)
{
	return (ms_setenv(env, "_", "./minishell"));
}

char	**ms_env_init(char **envp)
{
	char	**copy;

	if (!envp)
		return (NULL);
	copy = copy_env(envp);
	if (!copy)
		return (NULL);
	copy = handle_shlvl(copy);
	copy = init_underscore(copy);
	return (copy);
}
