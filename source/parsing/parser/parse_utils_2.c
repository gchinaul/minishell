/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:48:38 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 17:49:23 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*new_ast_node(t_enum_cmd type)
{
	t_ast	*node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->ful_path = NULL;
	node->full_cmd = NULL;
	node->argv = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->append_mode = 0;
	node->stderr_to_devnull = 0;
	node->heredoc_delimiter = NULL;
	node->child = 0;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	fill_simple_cmd(t_ast *node, t_list *tokens)
{
	fill_cmd_argv(node, tokens);
	node->full_cmd = node->argv;
	if (fill_cmd_redir(node, tokens) != 0)
	{
		node->type = CMD_INVALID;
	}
}

t_ast	*parse_command(t_list *tokens)
{
	t_ast	*result;

	result = parse_command_recursive(tokens);
	free_tokens(&tokens);
	return (result);
}
