/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:36:16 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 15:09:25 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	free_split_result(char **result, size_t j)
{
	while (j > 0)
		free(result[--j]);
	free(result);
}

int	split_loop(const char *s, char c, char **result)
{
	size_t	len;

	len = ft_strlen(s);
	return (split_fill(s, c, result, len));
}

int	split_fill(const char *s, char c, char **result, size_t len)
{
	t_split_ctx	ctx;
	size_t		j;

	j = 0;
	ctx.i = 0;
	ctx.start = 0;
	ctx.len = len;
	while (ctx.i < ctx.len)
	{
		if (find_next_word_s(s, c, &ctx))
		{
			result[j] = extract_word_s(s, ctx.start, ctx.i);
			if (!result[j])
			{
				free_split_result(result, j);
				return (0);
			}
			j++;
		}
	}
	result[j] = NULL;
	return (1);
}
