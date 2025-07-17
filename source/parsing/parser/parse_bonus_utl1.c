/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus_utl1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:50:32 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 18:01:44 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_last_logical_operator(t_list *tokens)
{
	t_token	*token;
	int		i;
	int		last_index;

	i = 0;
	last_index = -1;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token && (token->type == AND || token->type == OR))
			last_index = i;
		tokens = tokens->next;
		i++;
	}
	return (last_index);
}

t_list	*ft_lstget_b(t_list *lst, int index)
{
	int	i;

	i = 0;
	while (lst && i < index)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}

int	find_last_l_oper_with_paren(t_list *tokens)
{
	t_token	*token;
	int		i;
	int		last_index;
	int		paren_level;

	i = 0;
	last_index = -1;
	paren_level = 0;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->type == LPAREN)
			paren_level++;
		else if (token->type == RPAREN)
			paren_level--;
		else if (paren_level == 0 && (token->type == AND || token->type == OR))
			last_index = i;
		tokens = tokens->next;
		i++;
	}
	return (last_index);
}
