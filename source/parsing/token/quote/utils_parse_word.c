/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:37:37 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 17:11:46 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_dollar(const char *s, int *i, char **value, t_expand_ctx *ctx)
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

int	handle_tilde(const char *s, int *i, char **value, t_expand_ctx *ctx)
{
	char	*expanded;
	char	*new_value;

	expanded = expand_tilde(s, i, ctx->env);
	if (!expanded)
		return (-1);
	new_value = ft_strjoin_free(*value, expanded);
	free(expanded);
	if (!new_value)
		return (-1);
	*value = new_value;
	return (0);
}
