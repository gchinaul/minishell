/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils_par.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:13:29 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 17:16:24 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_expanded_variable_ctx(const char *s, int *i, char **value,
		t_expand_ctx *ctx)
{
	char	*expanded;
	char	*new_value;

	expanded = expand_variable(s, i, ctx->env, ctx->exit_status);
	if (!expanded)
		return (-1);
	new_value = ft_strjoin_free(*value, expanded);
	free(expanded);
	if (!new_value)
		return (-1);
	*value = new_value;
	return (0);
}

int	handle_double_quote_content_ctx(const char *s, int *i, char **value,
		t_expand_ctx *ctx)
{
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '$')
		{
			if (append_expanded_variable_ctx(s, i, value, ctx) < 0)
				return (-1);
		}
		else
		{
			if (append_char_to_value(value, s[*i]) < 0)
				return (-1);
			(*i)++;
		}
	}
	if (s[*i] != '"')
	{
		printf("Syntax error: unclosed double quote\n");
		return (-1);
	}
	return (0);
}
