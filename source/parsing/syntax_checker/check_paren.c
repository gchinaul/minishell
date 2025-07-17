/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paren.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:12:11 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 12:13:21 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_parentheses_content(t_list *curr)
{
	if (is_empty_parentheses(curr))
	{
		print_syntax_error(")");
		return (ERROR);
	}
	return (0);
}

static int	handle_left_paren(t_list *curr, int *paren)
{
	(*paren)++;
	if (check_parentheses_content(curr) == ERROR)
		return (ERROR);
	return (0);
}

static int	handle_right_paren(int *paren)
{
	if (*paren == 0)
	{
		print_syntax_error(")");
		return (ERROR);
	}
	(*paren)--;
	return (0);
}

static int	process_paren_token(t_token *tok, t_list *curr, int *paren)
{
	if (tok->type == LPAREN)
		return (handle_left_paren(curr, paren));
	if (tok->type == RPAREN)
		return (handle_right_paren(paren));
	return (0);
}

int	check_parentheses(t_list *tokens)
{
	int		paren;
	t_list	*curr;
	t_token	*tok;

	paren = 0;
	curr = tokens;
	while (curr)
	{
		tok = (t_token *)curr->content;
		if (process_paren_token(tok, curr, &paren) == ERROR)
			return (ERROR);
		curr = curr->next;
	}
	if (paren != 0)
	{
		print_syntax_error("newline");
		return (ERROR);
	}
	return (0);
}
