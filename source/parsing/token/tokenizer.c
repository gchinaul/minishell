/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:33:37 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 16:52:32 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize(const char *input, t_list **tokens, char **env, int exit_status)
{
	char				*input_dup;
	char				*cleaned;
	int					result;
	t_tokenize_context	ctx;

	ctx.tokens = tokens;
	ctx.env = env;
	ctx.exit_status = exit_status;
	input_dup = ft_strdup(input);
	if (!input_dup)
		return (0);
	cleaned = ft_input_cleaner(input_dup);
	if (!cleaned)
		return (0);
	result = tokenize_loop_t(cleaned, &ctx);
	free(cleaned);
	return (result);
}
