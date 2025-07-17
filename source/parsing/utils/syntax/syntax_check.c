/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:45:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 09:44:11 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirect_type(int type)
{
	return (type == REDIR_IN || type == REDIR_OUT || type == REDIR_APPEND
		|| type == HEREDOC);
}

static int	check_pipe_syntax(t_list *tokens)
{
	t_list	*current;
	t_token	*token;
	t_token	*prev_token;

	current = tokens;
	prev_token = NULL;
	while (current)
	{
		token = (t_token *)current->content;
		if (token->type == PIPE)
		{
			if (!prev_token || prev_token->type == PIPE)
				return (pipe_syntax_error("|"));
			if (!current->next)
				return (pipe_syntax_error("newline"));
		}
		prev_token = token;
		current = current->next;
	}
	return (1);
}

static int	check_redirect_token(t_list *current)
{
	t_token	*token;
	t_token	*next_token;

	token = (t_token *)current->content;
	if (is_redirect_type(token->type))
	{
		if (!current->next)
		{
			print_syntax_error("newline");
			return (0);
		}
		next_token = (t_token *)current->next->content;
		if (next_token->type != WORD)
		{
			print_syntax_error(next_token->value);
			return (0);
		}
	}
	return (1);
}

static int	check_redirect_syntax(t_list *tokens)
{
	t_list	*current;

	current = tokens;
	while (current)
	{
		if (!check_redirect_token(current))
			return (0);
		current = current->next;
	}
	return (1);
}

int	validate_syntax(t_list *tokens)
{
	if (!tokens)
		return (1);
	if (!check_pipe_syntax(tokens))
		return (0);
	if (!check_redirect_syntax(tokens))
		return (0);
	if (checker_syntax(tokens) == ERROR)
		return (0);
	return (1);
}
