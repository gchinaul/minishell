/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:59:04 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 18:52:57 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*find_right_start(t_list *tokens, int index)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = tokens;
	while (tmp && i < index)
	{
		tmp = tmp->next;
		i++;
	}
	if (tmp)
		return (tmp->next);
	else
		return (NULL);
}

static void	truncate_left_list(t_list *left, int index)
{
	int		i;
	t_list	*tmp;
	t_list	*to_free;

	i = 0;
	tmp = left;
	while (tmp && i < index - 1)
	{
		tmp = tmp->next;
		i++;
	}
	if (tmp && tmp->next)
	{
		to_free = tmp->next;
		tmp->next = NULL;
		free_tokens(&to_free);
	}
}

void	split_token(t_list *tokens, int index, t_list **left, t_list **right)
{
	t_list	*right_start;

	right_start = find_right_start(tokens, index);
	*left = duplicate_token_list(tokens);
	if (*left)
		truncate_left_list(*left, index);
	*right = duplicate_token_list(right_start);
}
