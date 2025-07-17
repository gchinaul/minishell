/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:28:19 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 16:29:42 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable_in_dquotes(const char *s, int *i, char **env,
		int exit_status)
{
	char	*name;
	char	*value;

	if (s[*i] != '$')
		return (ft_strdup(""));
	(*i)++;
	if (!s[*i] || s[*i] == ' ' || s[*i] == '\t' || s[*i] == '"')
		return (ft_strdup("$"));
	name = get_var_name_v(s, i);
	if (!name)
		return (NULL);
	if (!*name)
	{
		free(name);
		return (ft_strdup("$"));
	}
	value = get_env_value_v(name, env, exit_status);
	free(name);
	return (value);
}

char	*expand_variable_in_quotes(const char *s, int *i, char **env,
		int exit_status)
{
	char	*name;
	char	*value;

	if (s[*i] != '$')
		return (ft_strdup(""));
	(*i)++;
	if (!s[*i] || s[*i] == '"')
	{
		(*i)--;
		return (ft_strdup("$"));
	}
	if (s[*i] == ' ' || s[*i] == '\t')
		return (ft_strdup("$"));
	name = get_var_name_v(s, i);
	if (!name)
		return (NULL);
	if (!*name)
	{
		free(name);
		return (ft_strdup("$"));
	}
	value = get_env_value_v(name, env, exit_status);
	free(name);
	return (value);
}

char	*get_var_name_v(const char *s, int *i)
{
	int		start;
	int		len;
	char	*name;

	start = *i;
	if (s[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	if (!ft_isalpha(s[*i]) && s[*i] != '_')
	{
		return (ft_strdup(""));
	}
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	len = *i - start;
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	ft_strncpy(name, &s[start], len);
	name[len] = '\0';
	return (name);
}

char	*get_env_value_v(const char *name, char **env, int exit_status)
{
	int	i;
	int	name_len;

	if (!name || !*name)
		return (ft_strdup(""));
	if (ft_strcmp(name, "?") == 0)
		return (ft_itoa(exit_status));
	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
			return (ft_strdup(&env[i][name_len + 1]));
		i++;
	}
	return (ft_strdup(""));
}
