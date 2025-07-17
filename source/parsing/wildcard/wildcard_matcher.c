/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_matcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:00:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 18:40:16 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int	match_pattern_wi(const char *pattern, const char *str)
{
	if (!*pattern && !*str)
		return (1);
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (!*pattern)
			return (1);
		while (*str)
		{
			if (match_pattern_wi(pattern, str))
				return (1);
			str++;
		}
		return (match_pattern_wi(pattern, str));
	}
	if (*pattern == *str)
		return (match_pattern_wi(pattern + 1, str + 1));
	return (0);
}

static void	split_pattern(const char *pattern, char **dir, char **filename)
{
	int	i;

	i = ft_strlen(pattern) - 1;
	while (i >= 0 && pattern[i] != '/')
		i--;
	if (i >= 0)
	{
		*dir = ft_substr(pattern, 0, i);
		*filename = ft_strdup(&pattern[i + 1]);
	}
	else
	{
		*dir = NULL;
		*filename = ft_strdup(pattern);
	}
}

static char	**wildcard_no_match(const char *pattern, char **matches)
{
	char	**result;

	if (matches)
		free(matches);
	result = malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	result[0] = ft_strdup(pattern);
	result[1] = NULL;
	return (result);
}

char	**expand_wildcard(const char *pattern)
{
	char	**matches;
	char	*dir;
	char	*filename;

	if (!pattern || !ft_strchr(pattern, '*'))
		return (NULL);
	split_pattern(pattern, &dir, &filename);
	matches = expand_wildcard_in_dir(filename, dir);
	free(dir);
	free(filename);
	if (!matches || !matches[0])
		return (wildcard_no_match(pattern, matches));
	return (matches);
}
