/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_log_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:55:51 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 18:04:56 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*create_logical_node(t_list *tokens, int index)
{
	t_list	*left_tok;
	t_list	*right_tok;
	t_token	*tok;
	t_ast	*node;

	tok = (t_token *)ft_lstget_b(tokens, index)->content;
	if (!tok)
		return (NULL);
	node = new_ast_node(tok->type);
	if (!node)
		return (NULL);
	split_token(tokens, index, &left_tok, &right_tok);
	if (!left_tok || !right_tok || left_tok == tokens || right_tok == tokens)
	{
		free_ast(node);
		return (NULL);
	}
	node->left = parse_command_recursive(left_tok);
	node->right = parse_command_recursive(right_tok);
	free_tokens(&left_tok);
	free_tokens(&right_tok);
	return (node);
}

t_ast	*parse_logical_command(t_list *tokens)
{
	int	index;

	index = find_last_l_oper_with_paren(tokens);
	if (index == -1)
		return (NULL);
	return (create_logical_node(tokens, index));
}
