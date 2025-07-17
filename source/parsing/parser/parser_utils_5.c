/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:15:48 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 12:20:39 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_argv_on_error_b(char **argv, int arg_count)
{
	int	i;

	i = arg_count - 1;
	while (i >= 0)
	{
		free(argv[i]);
		i--;
	}
	free(argv);
}

int	process_token_b(char ***argv, int *capacity, int *arg_count, t_token *tok)
{
	if (tok->type == WORD)
	{
		if (add_expanded_args(argv, capacity, arg_count, tok->value) < 0)
			return (-1);
	}
	return (0);
}

int	fill_args_loop_b(char ***argv, t_list *tokens, int *arg_count,
		int *capacity)
{
	int		skip_next;
	t_token	*tok;

	skip_next = 0;
	while (tokens)
	{
		tok = (t_token *)tokens->content;
		if (skip_next)
			skip_next = 0;
		else if (tok->type == REDIR_IN || tok->type == REDIR_OUT
			|| tok->type == REDIR_APPEND || tok->type == HEREDOC)
			skip_next = 1;
		else
		{
			if (process_token_b(argv, capacity, arg_count, tok) < 0)
				return (-1);
		}
		tokens = tokens->next;
	}
	return (0);
}

int	ensure_argv_capacity(char ***argv_ptr, int *capacity, int needed)
{
	char	**new_argv;
	int		i;

	if (needed < *capacity)
		return (0);
	*capacity *= 2;
	new_argv = malloc(sizeof(char *) * (*capacity));
	if (!new_argv)
		return (-1);
	i = 0;
	while (i < needed)
	{
		new_argv[i] = (*argv_ptr)[i];
		i++;
	}
	free(*argv_ptr);
	*argv_ptr = new_argv;
	return (0);
}

void	add_expanded_to_argv(char ***argv_ptr, int *count, char **expanded)
{
	int	i;

	i = 0;
	while (expanded[i])
	{
		(*argv_ptr)[*count] = expanded[i];
		(*count)++;
		i++;
	}
}
