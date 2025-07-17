/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:34:59 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 12:20:31 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_expanded(char **expanded)
{
	int	i;

	i = 0;
	if (!expanded)
		return ;
	while (expanded[i])
	{
		free(expanded[i]);
		i++;
	}
	free(expanded);
}

int	add_expanded_args(char ***argv_ptr, int *capacity, int *count,
		const char *token_value)
{
	char	**expanded;
	int		expanded_count;

	if (!token_value)
	{
		(*argv_ptr)[(*count)++] = ft_strdup("");
		return (0);
	}
	expanded = expand_wildcard(token_value);
	if (!expanded)
	{
		(*argv_ptr)[(*count)++] = ft_strdup(token_value);
		return (0);
	}
	expanded_count = 0;
	while (expanded[expanded_count])
		expanded_count++;
	if (ensure_argv_capacity(argv_ptr, capacity, *count + expanded_count) < 0)
	{
		free_expanded(expanded);
		return (-1);
	}
	add_expanded_to_argv(argv_ptr, count, expanded);
	free(expanded);
	return (0);
}

static int	allocate_initial_argv(char ***argv, int capacity)
{
	*argv = malloc(sizeof(char *) * capacity);
	if (!*argv)
		return (-1);
	return (0);
}

static int	finalize_argv(char ***argv, int arg_count)
{
	(*argv)[arg_count] = NULL;
	return (0);
}

void	fill_cmd_args_b(t_ast *node, t_list *tokens, int count)
{
	char	**argv;
	int		capacity;
	int		arg_count;

	capacity = count + 10;
	if (allocate_initial_argv(&argv, capacity) < 0)
	{
		node->argv = NULL;
		return ;
	}
	arg_count = 0;
	if (fill_args_loop_b(&argv, tokens, &arg_count, &capacity) < 0)
	{
		free_argv_on_error_b(argv, arg_count);
		node->argv = NULL;
		return ;
	}
	finalize_argv(&argv, arg_count);
	node->argv = argv;
}
