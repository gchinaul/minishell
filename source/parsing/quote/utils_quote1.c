/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quote1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:30:34 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 17:43:02 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_dollar_in_dquotes(const char *s, int *i, char **value,
		t_expand_ctx *ctx)
{
	char	*expanded;
	char	*new_value;

	expanded = expand_variable_in_dquotes(s, i, ctx->env, ctx->exit_status);
	if (!expanded)
		return (-1);
	new_value = ft_strjoin_free(*value, expanded);
	free(expanded);
	if (!new_value)
		return (-1);
	*value = new_value;
	return (0);
}

int	handle_double_quote_expansion(const char *s, int *i, char **value,
		t_expand_ctx *ctx)
{
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '$')
		{
			if (handle_dollar_in_dquotes(s, i, value, ctx) < 0)
				return (-1);
		}
		else
		{
			if (append_char_to_value(value, s[*i]) < 0)
				return (-1);
			(*i)++;
		}
	}
	return (0);
}

int	handle_double_quote(const char *s, int *i, char **value, t_expand_ctx *ctx)
{
	int	start_len;

	(*i)++;
	if (*value)
		start_len = (int)strlen(*value);
	else
		start_len = 0;
	if (handle_double_quote_expansion(s, i, value, ctx) < 0)
		return (-1);
	if (s[*i] != '"')
	{
		printf("Syntax error: unclosed double quote\n");
		return (-1);
	}
	(*i)++;
	return (ensure_value_initialized(value, start_len));
}

int	handle_exit_status(char **value, int *i, t_expand_ctx *ctx)
{
	char	*var_value;
	char	*new_value;

	*i += 2;
	var_value = ft_itoa(ctx->exit_status);
	if (!var_value)
		return (-1);
	new_value = ft_strjoin_free(*value, var_value);
	free(var_value);
	if (!new_value)
		return (-1);
	*value = new_value;
	return (0);
}
