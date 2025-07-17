/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 23:00:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 16:44:59 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**word_split_empty_case(void)
{
	char	**result;

	result = malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	result[0] = ft_strdup("");
	result[1] = NULL;
	return (result);
}

static char	**word_split_trimmed_empty(char *copy)
{
	char	**result;

	result = malloc(sizeof(char *) * 1);
	free(copy);
	if (!result)
		return (NULL);
	result[0] = NULL;
	return (result);
}

static char	**word_split_extract(const char *trimmed, int count, char *copy)
{
	char	**result;
	int		fail_idx;

	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
	{
		free(copy);
		return (NULL);
	}
	fail_idx = extract_words_ws(trimmed, result, count);
	if (fail_idx != -1)
	{
		free_split_result_ws(result, fail_idx, copy);
		return (NULL);
	}
	free(copy);
	return (result);
}

char	**word_split(const char *str)
{
	char	*trimmed;
	char	*copy;
	int		count;

	if (!str || !*str)
		return (word_split_empty_case());
	copy = ft_strdup(str);
	if (!copy)
		return (NULL);
	trimmed = trim_leading_ifs(copy);
	trimmed = trim_trailing_ifs(trimmed);
	if (!*trimmed)
		return (word_split_trimmed_empty(copy));
	count = count_words_ws(trimmed);
	return (word_split_extract(trimmed, count, copy));
}
