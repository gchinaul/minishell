/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniz_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:50:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 16:53:34 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_operator_t(const char *s, int i, t_token *token)
{
	int	res;

	res = parse_double_operator(s, i, token);
	if (res != i)
		return (res);
	res = parse_single_operator(s, i, token);
	if (res != i)
		return (res);
	return (-1);
}

int	tokenize_loop_t(char *cleaned, t_tokenize_context *ctx)
{
	int	i;
	int	res;
	int	new_i;

	i = 0;
	while (cleaned[i])
	{
		i = skip_spaces(cleaned, i);
		if (!cleaned[i])
			break ;
		res = process_token(cleaned, i, ctx, &new_i);
		if (res == -1 || res == 0)
		{
			free_tokens(ctx->tokens);
			*(ctx->tokens) = NULL;
			return (0);
		}
		i = new_i;
	}
	return (1);
}

t_token	*alloc_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = NULL;
	token->type = 0;
	return (token);
}
