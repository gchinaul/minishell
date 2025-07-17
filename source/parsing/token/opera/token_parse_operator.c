/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse_operator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:14:40 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 17:04:36 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_or_operator(const char *s, int i, t_token *token)
{
	if (s[i] == '|' && s[i + 1] == '|')
	{
		token->type = OR;
		token->value = ft_strdup("||");
		if (!token->value)
			return (-1);
		return (i + 2);
	}
	return (i);
}

static int	parse_and_operator(const char *s, int i, t_token *token)
{
	if (s[i] == '&' && s[i + 1] == '&')
	{
		token->type = AND;
		token->value = ft_strdup("&&");
		if (!token->value)
			return (-1);
		return (i + 2);
	}
	return (i);
}

static int	parse_append_operator(const char *s, int i, t_token *token)
{
	if (s[i] == '>' && s[i + 1] == '>')
	{
		token->type = REDIR_APPEND;
		token->value = ft_strdup(">>");
		if (!token->value)
			return (-1);
		return (i + 2);
	}
	return (i);
}

static int	parse_heredoc_operator(const char *s, int i, t_token *token)
{
	if (s[i] == '<' && s[i + 1] == '<')
	{
		token->type = HEREDOC;
		token->value = ft_strdup("<<");
		if (!token->value)
			return (-1);
		return (i + 2);
	}
	return (i);
}

int	parse_double_operator(const char *s, int i, t_token *token)
{
	int	res;

	res = parse_or_operator(s, i, token);
	if (res != i)
		return (res);
	res = parse_and_operator(s, i, token);
	if (res != i)
		return (res);
	res = parse_append_operator(s, i, token);
	if (res != i)
		return (res);
	res = parse_heredoc_operator(s, i, token);
	return (res);
}
