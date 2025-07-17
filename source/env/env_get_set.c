/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 21:27:09 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/27 10:47:51 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_getenv(char **env, const char *key, int n)
{
	int	i;
	int	key_len;

	(void)n;
	if (!key || !env)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, key_len) && env[i][key_len] == '=')
			return (env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

char	**ms_env_add(char **env, char *entry)
{
	char	**new_env;
	int		len;
	int		i;

	if (!entry)
		return (env);
	len = ft_matrixlen(env);
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (env);
	i = 0;
	while (i < len)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = ft_strdup(entry);
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}

char	**ms_setenv(char **env, const char *key, const char *value)
{
	char	*new_var;
	char	**result;
	int		i;
	int		key_len;

	i = -1;
	key_len = ft_strlen(key);
	new_var = ft_strjoin_3(key, "=", value);
	if (!new_var)
		return (env);
	while (env && env[++i])
	{
		if (!ft_strncmp(env[i], key, key_len) && env[i][key_len] == '=')
		{
			free(env[i]);
			env[i] = new_var;
			return (env);
		}
	}
	result = ms_env_add(env, new_var);
	free(new_var);
	return (result);
}
