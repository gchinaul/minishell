/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:45:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 22:50:19 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "user_info.h"

/* Character type utilities */
int		in_ctype_ok(int c);
int		ft_isspace(int c);
int		ft_operator(int c);
int		ft_quote(int c);
int		is_ifs_char(char c);

/* String processing */
char	*trim_leading_ifs(const char *str);
char	*trim_trailing_ifs(char *str);
int		count_words_ws(const char *trimmed);
void	free_split_result_ws(char **result, int j, char *copy);
int		extract_words_ws(const char *trimmed, char **result, int count);

/* Echo utilities */
int		echo_builtin_improved(char **args);
char	**process_quotes_in_args(char **args);

/* Main loop utilities */
int		minishell_loop(char **envp);
void	init_user_info_m(t_user_info *user, char **envp);
void	cleanup_user_info_m(t_user_info *user);
void	process_input_m(char *input, t_user_info *user, int *exiter);

#endif
