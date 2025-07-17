/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:52:10 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 17:25:05 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_token_value(char *cleaned, int i, t_token *token,
		t_tokenize_context *ctx)
{
	t_parse_word_ctx	pw_ctx;

	if (is_operator(cleaned[i]) || is_digit_redirection(cleaned, i))
		return (parse_operator_t(cleaned, i, token));
	else
	{
		pw_ctx.s = cleaned;
		pw_ctx.i = i;
		pw_ctx.token = token;
		pw_ctx.expand_ctx.env = ctx->env;
		pw_ctx.expand_ctx.exit_status = ctx->exit_status;
		return (parse_word_ctx(&pw_ctx));
	}
}

static int	handle_token_error(t_token *token)
{
	free(token->value);
	free(token);
	return (-1);
}

static int	skip_empty_token(t_token *token, int res, int *new_index)
{
	if (!token->value || (token->type == WORD && strlen(token->value) == 0))
	{
		free(token->value);
		free(token);
		*new_index = res;
		return (1);
	}
	return (0);
}

static int	add_token_to_list(t_token *token, t_tokenize_context *ctx)
{
	t_list	*new_node;

	new_node = ft_lstnew(token);
	if (!new_node)
	{
		free(token->value);
		free(token);
		free_tokens(ctx->tokens);
		*(ctx->tokens) = NULL;
		return (-1);
	}
	ft_lstadd_back(ctx->tokens, new_node);
	return (1);
}

int	process_token(char *cleaned, int i, t_tokenize_context *ctx, int *new_index)
{
	t_token	*token;
	int		res;

	token = alloc_token();
	if (!token)
		return (0);
	res = parse_token_value(cleaned, i, token, ctx);
	if (res == -1)
		return (handle_token_error(token));
	if (skip_empty_token(token, res, new_index))
		return (1);
	if (!token->value)
		token->value = ft_strdup("");
	*new_index = res;
	return (add_token_to_list(token, ctx));
}
