/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:43:20 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 18:48:14 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_content(t_list *a, t_list *b)
{
	char	*tmp;

	tmp = (char *)a->content;
	a->content = b->content;
	b->content = tmp;
}

static int	bubble_pass(t_list *files)
{
	t_list	*current;
	int		swapped;

	swapped = 0;
	current = files;
	while (current->next)
	{
		if (ft_strcmp((char *)current->content,
				(char *)current->next->content) > 0)
		{
			swap_content(current, current->next);
			swapped = 1;
		}
		current = current->next;
	}
	return (swapped);
}

t_list	*sort_files(t_list *files)
{
	if (!files || !files->next)
		return (files);
	while (bubble_pass(files))
		;
	return (files);
}

int	is_hidden_w(const char *name)
{
	return (name[0] == '.');
}

int	match_simple_w(const char *pattern, const char *str)
{
	while (*pattern && *str)
	{
		if (*pattern == '*')
		{
			pattern++;
			if (!*pattern)
				return (1);
			while (*str)
			{
				if (match_simple_w(pattern, str))
					return (1);
				str++;
			}
			return (0);
		}
		if (*pattern != *str)
			return (0);
		pattern++;
		str++;
	}
	while (*pattern == '*')
		pattern++;
	return (!*pattern && !*str);
}
