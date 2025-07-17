/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:46:17 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 17:49:41 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*parse_pipe_command(t_list *tokens, int index)
{
	t_list	*left_tok;
	t_list	*right_tok;
	t_ast	*node;

	node = new_ast_node(PIPE);
	split_token(tokens, index, &left_tok, &right_tok);
	node->left = parse_command_recursive(left_tok);
	node->right = parse_command_recursive(right_tok);
	free_tokens(&left_tok);
	free_tokens(&right_tok);
	return (node);
}

static t_ast	*parse_by_type(t_list *tokens)
{
	t_ast	*node;

	node = parse_simple_command(&tokens);
	if (node != NULL)
		return (node);
	node = parse_logical_command(tokens);
	if (node != NULL)
		return (node);
	return (NULL);
}

t_ast	*parse_command_recursive(t_list *tokens)
{
	int		index;
	t_ast	*node;

	if (!tokens)
		return (NULL);
	node = parse_by_type(tokens);
	if (node)
		return (node);
	index = find_last_pipe(tokens);
	if (index != -1)
		return (parse_pipe_command(tokens, index));
	node = new_ast_node(SIMPLE);
	fill_simple_cmd(node, tokens);
	return (node);
}
