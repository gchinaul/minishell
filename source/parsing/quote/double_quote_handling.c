/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_handling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:30:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/27 20:30:00 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_value(const char *s, int start, int end, t_expand_ctx *ctx)
{
	char	*var_name;
	char	*var_value;
	int		len;

	len = end - start + 1;
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);
	ft_strncpy(var_name, &s[start], len);
	var_name[len] = '\0';
	var_value = ms_getenv(ctx->env, var_name, 1);
	if (!var_value)
		var_value = ft_strdup("");
	free(var_name);
	return (var_value);
}

static int	handle_env_variable(const char *s, int *i, char **value,
		t_expand_ctx *ctx)
{
	int		start;
	char	*var_value;
	char	*new_value;

	start = *i + 1;
	while (s[*i + 1] && (ft_isalnum(s[*i + 1]) || s[*i + 1] == '_'))
		(*i)++;
	var_value = get_env_value(s, start, *i, ctx);
	(*i)++;
	if (!var_value)
		return (-1);
	new_value = ft_strjoin_free(*value, var_value);
	free(var_value);
	if (!new_value)
		return (-1);
	*value = new_value;
	return (0);
}

static int	handle_dollar_literal(char **value, int *i)
{
	char	*var_value;
	char	*new_value;

	var_value = ft_strdup("$");
	(*i)++;
	if (!var_value)
		return (-1);
	new_value = ft_strjoin_free(*value, var_value);
	free(var_value);
	if (!new_value)
		return (-1);
	*value = new_value;
	return (0);
}

int	handle_double_quote_variable(const char *s, int *i, char **value,
		t_expand_ctx *ctx)
{
	int	start;

	start = *i + 1;
	if (s[start] == '?')
		return (handle_exit_status(value, i, ctx));
	else if (ft_isalpha(s[start]) || s[start] == '_')
		return (handle_env_variable(s, i, value, ctx));
	else
		return (handle_dollar_literal(value, i));
}
