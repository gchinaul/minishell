/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcar_matcher_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:38:13 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 18:42:43 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_matches(DIR *d, t_match_ctx *ctx)
{
	struct dirent	*entry;

	entry = readdir(d);
	while (entry != NULL)
	{
		check_and_add_w(entry, ctx);
		entry = readdir(d);
	}
}

void	check_and_add_w(struct dirent *entry, t_match_ctx *ctx)
{
	if (entry->d_name[0] == '.' && ctx->pattern[0] != '.')
		return ;
	if (match_pattern_wi(ctx->pattern, entry->d_name))
		add_match_to_array_w(ctx, entry->d_name);
}
