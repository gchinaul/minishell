/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:45:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 18:47:03 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <locale.h>
#include <sys/stat.h>

static char	**wildcard_no_match_improved(const char *pattern)
{
	char	**result;

	result = malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	result[0] = ft_strdup(pattern);
	result[1] = NULL;
	return (result);
}

static t_list	*collect_matches(DIR *dir, const char *pattern)
{
	struct dirent	*entry;
	t_list			*matches;
	t_list			*new_node;

	matches = NULL;
	entry = readdir(dir);
	while (entry)
	{
		if (is_hidden_w(entry->d_name) && pattern[0] != '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_simple_w(pattern, entry->d_name))
		{
			new_node = ft_lstnew(ft_strdup(entry->d_name));
			if (new_node)
				ft_lstadd_back(&matches, new_node);
		}
		entry = readdir(dir);
	}
	return (matches);
}

static char	**matches_to_array(t_list *matches, int count)
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

char	**expand_wildcard_improved(const char *pattern)
{
	DIR		*dir;
	t_list	*matches;
	char	**result;
	int		count;

	if (!ft_strchr(pattern, '*'))
		return (wildcard_no_match_improved(pattern));
	dir = opendir(".");
	if (!dir)
		return (NULL);
	matches = collect_matches(dir, pattern);
	closedir(dir);
	if (!matches)
		return (wildcard_no_match_improved(pattern));
	matches = sort_files(matches);
	count = ft_lstsize(matches);
	result = matches_to_array(matches, count);
	ft_lstclear(&matches, free);
	return (result);
}
