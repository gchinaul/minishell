/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:20:13 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 18:26:52 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int	match_pattern_w(const char *pattern, const char *str)
{
	if (!*pattern)
		return (!*str);
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (!*pattern)
			return (1);
		while (*str)
		{
			if (match_pattern_w(pattern, str))
				return (1);
			str++;
		}
		return (match_pattern_w(pattern, str));
	}
	if (*pattern == *str)
		return (match_pattern_w(pattern + 1, str + 1));
	return (0);
}

static void	add_match_to_list(const char *filename, t_list **matches)
{
	t_list	*new_node;
	char	*dup;

	dup = ft_strdup(filename);
	if (dup)
	{
		new_node = ft_lstnew(dup);
		if (new_node)
			ft_lstadd_back(matches, new_node);
		else
			free(dup);
	}
}

static void	check_and_add_match(const char *pattern, struct dirent *entry,
		t_list **matches)
{
	if (entry->d_name[0] == '.' && pattern[0] != '.')
		return ;
	if (match_pattern_w(pattern, entry->d_name))
		add_match_to_list(entry->d_name, matches);
}

t_list	*get_matching_files_w(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*matches;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	matches = NULL;
	entry = readdir(dir);
	while (entry != NULL)
	{
		check_and_add_match(pattern, entry, &matches);
		entry = readdir(dir);
	}
	closedir(dir);
	return (matches);
}
