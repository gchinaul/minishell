/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:32:51 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 12:43:49 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redir_in(t_ast *node, t_token *tok, t_list *tmp)
{
	int		fd;
	char	*filename;

	(void)tok;
	filename = ((t_token *)tmp->next->content)->value;
	if (check_ambiguous_redirect(filename))
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return (1);
	}
	close(fd);
	if (node->infile)
		free(node->infile);
	node->infile = ft_strdup(filename);
	return (0);
}

static int	handle_heredoc_b(t_ast *node, t_list *tmp)
{
	if (node->heredoc_delimiter)
		free(node->heredoc_delimiter);
	node->heredoc_delimiter = ft_strdup(((t_token *)tmp->next->content)->value);
	return (0);
}

int	open_outfile(char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror(filename);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	process_redir_token(t_ast *node, t_token *tok, t_list *tmp)
{
	if (tok->type == REDIR_IN && tmp->next)
	{
		if (handle_redir_in(node, tok, tmp))
			return (1);
	}
	else if (tok->type == HEREDOC && tmp->next)
		handle_heredoc_b(node, tmp);
	else if ((tok->type == REDIR_OUT || tok->type == REDIR_APPEND) && tmp->next)
	{
		if (ft_strncmp(tok->value, "2>/dev/null", 11) == 0)
			handle_stderr_devnull(node);
		else if (handle_redir_out_r(node, tok, tmp))
			return (1);
	}
	return (0);
}

int	fill_cmd_redir(t_ast *node, t_list *tokens)
{
	t_token	*tok;
	t_list	*tmp;

	tmp = tokens;
	while (tmp)
	{
		tok = (t_token *)tmp->content;
		if (process_redir_token(node, tok, tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
