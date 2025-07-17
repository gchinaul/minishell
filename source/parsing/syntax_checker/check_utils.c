/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:01:37 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 12:13:23 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty_parentheses(t_list *curr)
{
	t_token	*next_tok;

	if (!curr->next)
		return (0);
	next_tok = (t_token *)curr->next->content;
	if (next_tok->type == RPAREN)
		return (1);
	return (0);
}
