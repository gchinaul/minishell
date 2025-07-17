/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 09:36:50 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 12:23:26 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_ast(t_ast *node, t_user_info *user, int *exiter)
{
	int	status;

	if (!node)
		return (0);
	if (node->type == CMD_INVALID)
		return (1);
	if (node->type == AND || node->type == OR)
	{
		status = execute_ast(node->left, user, exiter);
		if ((node->type == AND && status == 0) || (node->type == OR
				&& status != 0))
			return (execute_ast(node->right, user, exiter));
		return (status);
	}
	if (node->type == PIPE)
		return (execute_pipe(node, user, exiter));
	if (node->type == SIMPLE)
	{
		return (execute_simple(node, user, exiter));
	}
	return (0);
}

int	prepare_heredocs(t_ast *node, char **env)
{
	if (!node)
		return (0);
	if (node->type == AND || node->type == OR)
	{
		if (prepare_heredocs(node->left, env) < 0)
			return (-1);
		return (prepare_heredocs(node->right, env));
	}
	if (node->type == PIPE)
	{
		if (prepare_heredocs(node->left, env) < 0)
			return (-1);
		return (prepare_heredocs(node->right, env));
	}
	if (node->type == SIMPLE && node->heredoc_delimiter)
	{
		return (handle_heredoc(node->heredoc_delimiter, env));
	}
	return (0);
}
