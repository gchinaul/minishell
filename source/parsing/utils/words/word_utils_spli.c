/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils_spli.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:39:51 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 16:43:59 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_ifs_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char	*trim_leading_ifs(const char *str)
{
	while (*str && is_ifs_char(*str))
		str++;
	return ((char *)str);
}

char	*trim_trailing_ifs(char *str)
{
	int	len;

	if (!str)
		return (str);
	len = ft_strlen(str);
	while (len > 0 && is_ifs_char(str[len - 1]))
	{
		str[len - 1] = '\0';
		len--;
	}
	return (str);
}

int	count_words_ws(const char *trimmed)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (trimmed[i])
	{
		if (!is_ifs_char(trimmed[i]))
		{
			count++;
			while (trimmed[i] && !is_ifs_char(trimmed[i]))
				i++;
		}
		else
			i++;
	}
	return (count);
}

void	free_split_result_ws(char **result, int j, char *copy)
{
	while (j > 0)
		free(result[--j]);
	free(result);
	free(copy);
}
