/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expand_improved.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:00:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 18:51:55 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_exit_status(int exit_status)
{
	return (ft_itoa(exit_status));
}

static char	*get_variable_name(const char *str, int *pos)
{
	int		start;
	int		len;
	char	*name;

	start = *pos;
	if (str[*pos] == '?')
	{
		(*pos)++;
		return (ft_strdup("?"));
	}
	if (!ft_isalpha(str[*pos]) && str[*pos] != '_')
		return (ft_strdup(""));
	while (str[*pos] && (ft_isalnum(str[*pos]) || str[*pos] == '_'))
		(*pos)++;
	len = *pos - start;
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	ft_strncpy(name, &str[start], len);
	name[len] = '\0';
	return (name);
}

char	*expand_variable_improved(const char *str, int *pos, char **env,
		int exit_status)
{
	char	*var_name;
	char	*var_value;
	char	*result;

	if (str[*pos] != '$')
		return (ft_strdup(""));
	(*pos)++;
	if (!str[*pos] || ft_isspace(str[*pos]) || str[*pos] == '"'
		|| str[*pos] == '\'')
		return (ft_strdup("$"));
	var_name = get_variable_name(str, pos);
	if (!var_name)
		return (NULL);
	if (ft_strcmp(var_name, "?") == 0)
	{
		free(var_name);
		return (expand_exit_status(exit_status));
	}
	var_value = get_env_var(var_name, env);
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	result = ft_strdup(var_value);
	free(var_value);
	return (result);
}
