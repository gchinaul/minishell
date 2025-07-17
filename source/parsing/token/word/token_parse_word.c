/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:13:16 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 12:13:20 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_backslash(const char *s, int *i, char **value)
{
	(*i)++;
	if (append_char_to_value(value, s[*i]) < 0)
		return (-1);
	(*i)++;
	return (0);
}

static int	process_char_ctx(const char *s, int *i, char **value,
		t_expand_ctx *ctx)
{
	if (s[*i] == '\\' && s[*i + 1])
		return (handle_backslash(s, i, value));
	else if (s[*i] == '\'')
		return (handle_single_quote(s, i, value));
	else if (s[*i] == '"')
		return (handle_double_quote_ctx(s, i, value, ctx));
	else if (s[*i] == '$')
		return (handle_dollar_ctx(s, i, value, ctx));
	else if (s[*i] == '~')
		return (handle_tilde_ctx(s, i, value, ctx));
	else
	{
		if (append_char_to_value(value, s[*i]) < 0)
			return (-1);
		(*i)++;
	}
	return (0);
}

static int	is_word_boundary(char c)
{
	if (ft_isspace(c))
		return (1);
	if (is_operator(c))
		return (1);
	return (0);
}

int	parse_word_ctx(t_parse_word_ctx *ctx)
{
	char	*value;
	int		ret;

	value = NULL;
	while (ctx->s[ctx->i] && !is_word_boundary(ctx->s[ctx->i]))
	{
		ret = process_char_ctx(ctx->s, &ctx->i, &value, &ctx->expand_ctx);
		if (ret < 0)
		{
			free(value);
			return (-1);
		}
	}
	ctx->token->type = WORD;
	if (value == NULL)
		value = ft_strdup("");
	ctx->token->value = value;
	if (value == NULL)
		return (-1);
	return (ctx->i);
}
