/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:33:23 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 12:43:15 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ambiguous_redirect(char *filename)
{
	char	**expanded;
	int		count;

	if (!ft_strchr(filename, '*'))
		return (0);
	expanded = expand_wildcards(filename);
	if (!expanded)
		return (0);
	count = 0;
	while (expanded[count])
		count++;
	if (count > 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putendl_fd(": ambiguous redirect", 2);
		ft_free_matrix(&expanded);
		return (1);
	}
	ft_free_matrix(&expanded);
	return (0);
}

void	handle_stderr_devnull(t_ast *node)
{
	node->stderr_to_devnull = 1;
}

int	handle_redir_out_r(t_ast *node, t_token *tok, t_list *tmp)
{
	int		flags;
	char	*filename;

	filename = ((t_token *)tmp->next->content)->value;
	if (check_ambiguous_redirect(filename))
		return (1);
	if (tok->type == REDIR_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (open_outfile(filename, flags) == -1)
		return (1);
	if (node->outfile)
		free(node->outfile);
	node->outfile = ft_strdup(filename);
	if (tok->type == REDIR_APPEND)
		node->append_mode = 1;
	else
		node->append_mode = 0;
	return (0);
}
