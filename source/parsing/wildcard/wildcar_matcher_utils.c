/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcar_matcher_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:30:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 18:42:22 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_match_to_array_w(t_match_ctx *ctx, const char *filename)
{
	if (ctx->dir)
		ctx->matches[*ctx->count] = ft_strjoin_3(ctx->dir, "/", filename);
	else
		ctx->matches[*ctx->count] = ft_strdup(filename);
	(*ctx->count)++;
}

static int	init_ctx_and_dir(const char *pattern, const char *dir,
		t_match_ctx *ctx, DIR **d)
{
	const char	*used_dir;

	if (dir)
		used_dir = dir;
	else
		used_dir = ".";
	*d = opendir(used_dir);
	if (!*d)
		return (0);
	ctx->pattern = pattern;
	ctx->dir = dir;
	ctx->matches = NULL;
	ctx->count = NULL;
	return (1);
}

static char	**alloc_and_fill_matches(DIR *d, t_match_ctx *ctx)
{
	char	**matches;
	int		count;

	matches = malloc(sizeof(char *) * 1000);
	if (!matches)
	{
		closedir(d);
		return (NULL);
	}
	count = 0;
	ctx->matches = matches;
	ctx->count = &count;
	fill_matches(d, ctx);
	closedir(d);
	matches[count] = NULL;
	return (matches);
}

char	**expand_wildcard_in_dir(const char *pattern, const char *dir)
{
	DIR			*d;
	t_match_ctx	ctx;

	if (!init_ctx_and_dir(pattern, dir, &ctx, &d))
		return (NULL);
	return (alloc_and_fill_matches(d, &ctx));
}
