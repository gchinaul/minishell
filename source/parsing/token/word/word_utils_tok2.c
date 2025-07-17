/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils_tok2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:19:23 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 17:22:10 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_double_quote_ctx(const char *s, int *i, char **value,
		t_expand_ctx *ctx)
{
	return (handle_double_quote(s, i, value, ctx));
}

int	handle_dollar_ctx(const char *s, int *i, char **value, t_expand_ctx *ctx)
{
	return (handle_dollar(s, i, value, ctx));
}

int	handle_tilde_ctx(const char *s, int *i, char **value, t_expand_ctx *ctx)
{
	return (handle_tilde(s, i, value, ctx));
}
