/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 09:57:50 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/27 09:48:33 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	ft_free_matrix(&node->argv);
	node->full_cmd = NULL;
	if (node->infile)
		free(node->infile);
	if (node->outfile)
		free(node->outfile);
	if (node->heredoc_delimiter)
		free(node->heredoc_delimiter);
	if (node->ful_path)
		free(node->ful_path);
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}
