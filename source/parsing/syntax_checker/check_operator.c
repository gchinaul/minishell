/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:44:06 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 09:44:09 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection_token(t_enum_cmd type)
{
	if (type == REDIR_IN || type == REDIR_OUT)
		return (1);
	if (type == REDIR_APPEND || type == HEREDOC)
		return (1);
	return (0);
}

static int	is_valid_redir_target(t_enum_cmd type)
{
	if (type == WORD || type == SIMPLE)
		return (1);
	return (0);
}

static int	check_consecutive_operators(t_token *tok, t_token *next)
{
	if ((tok->type == PIPE || tok->type == AND || tok->type == OR)
		&& (next->type == PIPE || next->type == AND || next->type == OR))
	{
		print_syntax_error(next->value);
		return (ERROR);
	}
	return (0);
}

static int	check_redirection_syntax(t_token *tok, t_token *next)
{
	if (is_redirection_token(tok->type) && !is_valid_redir_target(next->type))
	{
		print_syntax_error(next->value);
		return (ERROR);
	}
	return (0);
}

int	check_operators(t_list *tokens)
{
	t_list	*curr;
	t_token	*tok;
	t_token	*next;

	curr = tokens;
	while (curr && curr->next)
	{
		tok = (t_token *)curr->content;
		next = (t_token *)curr->next->content;
		if (check_consecutive_operators(tok, next) == ERROR)
			return (ERROR);
		if (check_redirection_syntax(tok, next) == ERROR)
			return (ERROR);
		curr = curr->next;
	}
	return (0);
}
