/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:28:56 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 13:30:58 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redir_token(t_token *tok, t_list *tmp)
{
	char	*infile;
	char	*outfile;

	if (tok->type == REDIR_IN && tmp->next)
	{
		infile = ((t_token *)tmp->next->content)->value;
		return (handle_input_redir(infile));
	}
	else if (tok->type == HEREDOC && tmp->next)
	{
		return (handle_heredoc_redir());
	}
	else if ((tok->type == REDIR_OUT || tok->type == REDIR_APPEND) && tmp->next)
	{
		outfile = ((t_token *)tmp->next->content)->value;
		return (handle_output_redir(outfile, tok->type));
	}
	return (0);
}

int	handle_multiple_redir_safe(t_list *tokens, char **env)
{
	t_token	*tok;
	t_list	*tmp;

	tmp = tokens;
	(void)env;
	while (tmp)
	{
		tok = (t_token *)tmp->content;
		if (handle_redir_token(tok, tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
