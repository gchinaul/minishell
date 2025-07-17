/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:30:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 17:35:34 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_quote_dispatch(const char *input, int *i, char **result,
		t_expand_ctx *ctx)
{
	if (input[*i] == '\'')
		return (handle_single_quote(input, i, result));
	else if (input[*i] == '"')
		return (handle_double_quote(input, i, result, ctx));
	else if (input[*i] == '$')
		return (handle_dollar(input, i, result, ctx));
	else if (input[*i] == '~')
		return (handle_tilde(input, i, result, ctx));
	else
		return (2);
}

static int	handle_other_char(const char *input, int *i, char **result)
{
	if (append_char_to_value(result, input[*i]) < 0)
		return (-1);
	(*i)++;
	return (0);
}

char	*remove_quotes_and_expand(const char *input, char **env)
{
	char			*result;
	int				i;
	t_expand_ctx	ctx;
	int				ret;

	result = NULL;
	i = 0;
	ctx.env = env;
	ctx.exit_status = 0;
	while (input[i])
	{
		ret = handle_quote_dispatch(input, &i, &result, &ctx);
		if (ret == 2)
			ret = handle_other_char(input, &i, &result);
		if (ret < 0)
			return (NULL);
	}
	if (!result)
		result = ft_strdup("");
	return (result);
}
