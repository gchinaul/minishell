/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:30:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 16:35:21 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_in_double_quotes(const char *s, int *i)
{
	char	*content;
	int		start;
	int		len;

	content = NULL;
	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '"')
		(*i)++;
	if (s[*i] == '"')
	{
		len = *i - start;
		content = malloc(len + 1);
		if (content)
		{
			ft_strncpy(content, &s[start], len);
			content[len] = '\0';
		}
		(*i)++;
	}
	if (content)
		return (content);
	else
		return (ft_strdup(""));
}

static char	*expand_in_single_quotes(const char *s, int *i)
{
	char	*content;
	int		start;
	int		len;

	content = NULL;
	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	if (s[*i] == '\'')
	{
		len = *i - start;
		content = malloc(len + 1);
		if (content)
		{
			ft_strncpy(content, &s[start], len);
			content[len] = '\0';
		}
		(*i)++;
	}
	if (content)
		return (content);
	else
		return (ft_strdup(""));
}

static char	*expand_variable_name(const char *s, int *i, char **env,
		int exit_status)
{
	char	*name;
	char	*value;

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

char	*expand_variable(const char *s, int *i, char **env, int exit_status)
{
	if (s[*i] != '$')
		return (ft_strdup(""));
	(*i)++;
	if (!s[*i] || s[*i] == ' ' || s[*i] == '\t')
		return (ft_strdup("$"));
	if (s[*i] == '"')
		return (expand_in_double_quotes(s, i));
	if (s[*i] == '\'')
		return (expand_in_single_quotes(s, i));
	return (expand_variable_name(s, i, env, exit_status));
}
