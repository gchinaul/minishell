/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:23:36 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 14:32:12 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote_state_c(t_copy_ctx *ctx, char c)
{
	if (c == '\'' && !ctx->in_double_quote)
		ctx->in_single_quote = !ctx->in_single_quote;
	else if (c == '"' && !ctx->in_single_quote)
		ctx->in_double_quote = !ctx->in_double_quote;
}

void	copy_char_c(t_copy_ctx *ctx, char c)
{
	ctx->output[ctx->j++] = c;
	ctx->in_word = 1;
}

void	handle_space_state_c(t_copy_ctx *ctx, char c)
{
	if (is_space(c))
	{
		if (ctx->in_single_quote || ctx->in_double_quote)
			copy_char_c(ctx, c);
		else if (ctx->in_word)
		{
			copy_char_c(ctx, ' ');
			ctx->in_word = 0;
		}
	}
}
