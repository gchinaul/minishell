/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:45:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 15:09:18 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

char	*extract_word_s(const char *s, size_t start, size_t end)
{
	char	*word;
	size_t	i;

	i = 0;
	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

int	find_next_word_s(const char *s, char c, t_split_ctx *ctx)
{
	while (ctx->i < ctx->len && s[ctx->i] == c)
		ctx->i++;
	ctx->start = ctx->i;
	while (ctx->i < ctx->len && s[ctx->i] != c)
		ctx->i++;
	return (ctx->start < ctx->i);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	if (!split_loop(s, c, result))
		return (NULL);
	return (result);
}
