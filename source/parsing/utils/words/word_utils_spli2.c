/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils_spli2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:42:59 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 16:45:34 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extract_words_ws(const char *trimmed, char **result, int count)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (trimmed[i] && j < count)
	{
		if (!is_ifs_char(trimmed[i]))
		{
			start = i;
			while (trimmed[i] && !is_ifs_char(trimmed[i]))
				i++;
			result[j] = malloc(i - start + 1);
			if (!result[j])
				return (j);
			ft_strncpy(result[j], &trimmed[start], i - start);
			result[j][i - start] = '\0';
			j++;
		}
		else
			i++;
	}
	result[j] = NULL;
	return (-1);
}
