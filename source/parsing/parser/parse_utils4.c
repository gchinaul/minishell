/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:05:59 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 18:07:02 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*create_token_node(t_token *token)
{
	t_list	*new_node;

	new_node = ft_lstnew(token);
	if (!new_node)
	{
		free(token->value);
		free(token);
		return (NULL);
	}
	return (new_node);
}

t_list	*duplicate_token_list(t_list *tokens)
{
	t_list	*new_list;
	t_list	*new_node;
	t_token	*new_token;
	t_list	*current;

	new_list = NULL;
	current = tokens;
	while (current)
	{
		new_token = duplicate_token((t_token *)current->content);
		if (!new_token)
		{
			free_tokens(&new_list);
			return (NULL);
		}
		new_node = create_token_node(new_token);
		if (!new_node)
		{
			free_tokens(&new_list);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		current = current->next;
	}
	return (new_list);
}

int	count_cmd_args_b(t_list *tokens)
{
	int		count;
	int		skip_next;
	t_token	*tok;

	count = 0;
	skip_next = 0;
	while (tokens)
	{
		tok = (t_token *)tokens->content;
		if (skip_next)
			skip_next = 0;
		else if (tok->type == REDIR_IN || tok->type == REDIR_OUT
			|| tok->type == REDIR_APPEND || tok->type == HEREDOC)
			skip_next = 1;
		else if (tok->type == WORD)
		{
			count++;
		}
		tokens = tokens->next;
	}
	return (count);
}
