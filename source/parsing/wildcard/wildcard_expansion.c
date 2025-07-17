/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:30:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 18:29:03 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static char	**wildcard_no_match(const char *pattern)
{
	char	**result;

	result = malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	result[0] = ft_strdup(pattern);
	result[1] = NULL;
	return (result);
}

static char	**wildcard_matches_to_array(t_list *matches, int count)
{
	char	**result;
	int		i;
	t_list	*current;

	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	current = matches;
	i = 0;
	while (current)
	{
		result[i] = ft_strdup((char *)current->content);
		current = current->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**expand_wildcards(const char *pattern)
{
	t_list	*matches;
	char	**result;
	int		count;

	if (!ft_strchr(pattern, '*'))
		return (wildcard_no_match(pattern));
	matches = get_matching_files_w(pattern);
	if (!matches)
		return (wildcard_no_match(pattern));
	count = ft_lstsize(matches);
	result = wildcard_matches_to_array(matches, count);
	ft_lstclear(&matches, free);
	return (result);
}
