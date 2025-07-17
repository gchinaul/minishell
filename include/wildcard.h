/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:45:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 22:50:18 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "ast.h"
# include "list.h"
# include <dirent.h>

/* Wildcard expansion */
char	**expand_wildcards(const char *pattern);
char	**expand_wildcard_improved(const char *pattern);
char	**expand_wildcard(const char *pattern);
char	**expand_wildcard_in_dir(const char *pattern, const char *dir);

/* Pattern matching */
int		match_pattern_w(const char *pattern, const char *str);
int		match_pattern_wi(const char *pattern, const char *str);
int		match_simple_w(const char *pattern, const char *str);

/* File matching */
t_list	*get_matching_files_w(const char *pattern);
void	fill_matches(DIR *d, t_match_ctx *ctx);
void	check_and_add_w(struct dirent *entry, t_match_ctx *ctx);
void	add_match_to_array_w(t_match_ctx *ctx, const char *filename);

/* Utilities */
int		is_hidden_w(const char *name);
t_list	*sort_files(t_list *files);

#endif
