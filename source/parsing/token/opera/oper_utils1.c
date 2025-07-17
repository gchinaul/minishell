/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:56:23 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 16:59:58 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_pipe_paren_operator(const char *s, int i, t_token *token)
{
	if (s[i] == '|')
	{
		token->type = PIPE;
		token->value = ft_strdup("|");
		if (!token->value)
			return (-1);
		return (i + 1);
	}
	if (s[i] == '(')
	{
		token->type = LPAREN;
		token->value = ft_strdup("(");
		if (!token->value)
			return (-1);
		return (i + 1);
	}
	if (s[i] == ')')
	{
		token->type = RPAREN;
		token->value = ft_strdup(")");
		if (!token->value)
			return (-1);
		return (i + 1);
	}
	return (i);
}

int	parse_single_operator(const char *s, int i, t_token *token)
{
	int	res;

	res = parse_pipe_paren_operator(s, i, token);
	if (res != i)
		return (res);
	return (parse_redirection_operator(s, i, token));
}

int	parse_redir_in(const char *s, int i, t_token *token)
{
	if (s[i] == '<')
	{
		token->type = REDIR_IN;
		token->value = ft_strdup("<");
		if (!token->value)
			return (-1);
		return (i + 1);
	}
	return (i);
}

int	parse_redir_devnull(const char *s, int i, t_token *token)
{
	if (s[i] == '2' && s[i + 1] == '>' && ft_strncmp(&s[i + 2], "/dev/null",
			9) == 0)
	{
		token->type = REDIR_OUT;
		token->value = ft_strdup("2>/dev/null");
		if (!token->value)
			return (-1);
		return (i + 11);
	}
	return (i);
}

int	parse_redir_out(const char *s, int i, t_token *token)
{
	if (s[i] == '>')
	{
		token->type = REDIR_OUT;
		token->value = ft_strdup(">");
		if (!token->value)
			return (-1);
		return (i + 1);
	}
	return (i);
}
