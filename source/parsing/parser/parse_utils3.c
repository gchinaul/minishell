/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:57:17 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 18:03:13 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*duplicate_token(t_token *token)
{
	t_token	*new_token;

	if (!token)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = token->type;
	if (token->value)
	{
		new_token->value = ft_strdup(token->value);
		if (!new_token->value)
		{
			free(new_token);
			return (NULL);
		}
	}
	else
		new_token->value = NULL;
	return (new_token);
}

int	find_last_pipe(t_list *tokens)
{
	int		i;
	int		index;
	t_list	*tmp;

	i = 0;
	index = -1;
	tmp = tokens;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == PIPE)
			index = i;
		tmp = tmp->next;
		i++;
	}
	return (index);
}

void	fill_cmd_argv(t_ast *node, t_list *tokens)
{
	int	count;

	count = count_cmd_args_b(tokens);
	fill_cmd_args_b(node, tokens, count);
}
