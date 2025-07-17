/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:16:18 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 14:32:27 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quotes_and_normal(t_copy_ctx *ctx, char c)
{
	if (c == '\'' || c == '"')
	{
		copy_char_c(ctx, c);
		handle_quote_state_c(ctx, c);
	}
	else if (!is_space(c))
		copy_char_c(ctx, c);
}

static void	copy_word_or_space(t_copy_ctx *ctx)
{
	char	c;

	c = ctx->input[ctx->i];
	handle_space_state_c(ctx, c);
	handle_quotes_and_normal(ctx, c);
	ctx->i++;
}

static void	init_copy_ctx(t_copy_ctx *ctx, const char *input, char *output)
{
	ctx->input = input;
	ctx->i = 0;
	ctx->output = output;
	ctx->j = 0;
	ctx->in_word = 0;
	ctx->in_single_quote = 0;
	ctx->in_double_quote = 0;
}

static int	clean_input_core(const char *input, char *output)
{
	t_copy_ctx	ctx;

	init_copy_ctx(&ctx, input, output);
	while (ctx.input[ctx.i] && is_space(ctx.input[ctx.i]))
		ctx.i++;
	while (ctx.input[ctx.i])
		copy_word_or_space(&ctx);
	if (ctx.j > 0 && ctx.output[ctx.j - 1] == ' ' && !ctx.in_single_quote
		&& !ctx.in_double_quote)
		ctx.j--;
	return (ctx.j);
}

char	*ft_input_cleaner(char *input)
{
	char	*cleaned;
	int		length;

	if (!input)
		return (NULL);
	cleaned = malloc(strlen(input) + 1);
	if (!cleaned)
		return (NULL);
	length = clean_input_core(input, cleaned);
	cleaned[length] = '\0';
	free(input);
	return (cleaned);
}
