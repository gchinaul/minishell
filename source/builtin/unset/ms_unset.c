/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:00:09 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 00:20:56 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_key_match(const char *env_entry, const char *key, int key_len)
{
	return (ft_strncmp(env_entry, key, key_len) == 0
		&& env_entry[key_len] == '=');
}

static int	copy_env_loop(char **env, char **new_env, const char *key,
		int key_len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env && env[i])
	{
		if (!is_key_match(env[i], key, key_len))
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j])
				return (j + 1);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (0);
}

static char	**copy_env_without_key(char **env, const char *key)
{
	int		key_len;
	int		env_len;
	char	**new_env;
	int		err;

	key_len = ft_strlen(key);
	env_len = ft_matrixlen(env);
	new_env = malloc(sizeof(char *) * (env_len + 1));
	if (!new_env)
		return (env);
	err = copy_env_loop(env, new_env, key, key_len);
	if (err)
	{
		free_new_env(new_env, err - 1);
		return (env);
	}
	ft_free_matrix(&env);
	return (new_env);
}

char	**ms_unsetenv(char **env, const char *key)
{
	return (copy_env_without_key(env, key));
}
