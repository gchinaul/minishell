/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:15:58 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/21 19:51:08 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_invalid_first_token(t_enum_cmd type)
{
	if (type == PIPE || type == AND || type == OR)
		return (1);
	return (0);
}

static int	is_invalid_last_token(t_enum_cmd type)
{
	if (type == PIPE || type == AND || type == OR)
		return (1);
	return (0);
}

static int	validate_token_positions(t_list *tokens)
{
	t_token	*first;
	t_token	*last_tok;
	t_list	*last;

	if (!tokens)
		return (ERROR);
	last = tokens;
	first = (t_token *)tokens->content;
	while (last->next)
		last = last->next;
	last_tok = (t_token *)last->content;
	if (is_invalid_first_token(first->type))
		return (ERROR);
	if (is_invalid_last_token(last_tok->type))
		return (ERROR);
	return (0);
}

int	checker_syntax(t_list *tokens)
{
	if (validate_token_positions(tokens) == ERROR)
		return (ERROR);
	if ((check_parentheses(tokens) == ERROR)
		|| (check_operators(tokens) == ERROR))
		return (ERROR);
	return (0);
}
