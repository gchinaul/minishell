/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:24:39 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 17:56:10 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*find_matching_rparen(t_list *start, int *paren_count)
{
	t_list	*current;
	t_token	*token;

	current = start;
	while (current && *paren_count > 0)
	{
		token = (t_token *)current->content;
		if (token->type == LPAREN)
			(*paren_count)++;
		else if (token->type == RPAREN)
			(*paren_count)--;
		if (*paren_count > 0)
			current = current->next;
	}
	return (current);
}

static t_list	*copy_tokens_between(t_list *start, t_list *end)
{
	t_list	*inner_tokens;
	t_list	*tmp;
	t_token	*new_token;
	t_list	*new_node;

	inner_tokens = NULL;
	tmp = start;
	while (tmp && tmp != end)
	{
		new_token = duplicate_token((t_token *)tmp->content);
		if (new_token)
		{
			new_node = ft_lstnew(new_token);
			if (new_node)
				ft_lstadd_back(&inner_tokens, new_node);
			else
			{
				free(new_token->value);
				free(new_token);
			}
		}
		tmp = tmp->next;
	}
	return (inner_tokens);
}

static t_ast	*parse_parenthesized_command(t_list *current)
{
	int		paren_count;
	t_list	*start;
	t_list	*end;
	t_list	*inner_tokens;
	t_ast	*result;

	paren_count = 1;
	start = current->next;
	end = find_matching_rparen(start, &paren_count);
	if (paren_count == 0 && start)
	{
		inner_tokens = copy_tokens_between(start, end);
		if (inner_tokens)
		{
			result = parse_command_recursive(inner_tokens);
			free_tokens(&inner_tokens);
			return (result);
		}
	}
	return (NULL);
}

t_ast	*parse_simple_command(t_list **tokens)
{
	t_list	*current;
	t_token	*first_token;

	if (!tokens || !*tokens)
		return (NULL);
	current = *tokens;
	first_token = (t_token *)current->content;
	if (first_token && first_token->type == LPAREN)
		return (parse_parenthesized_command(current));
	return (NULL);
}
