/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:12:52 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 16:47:53 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&' || c == '('
		|| c == ')');
}

int	is_digit_redirection(const char *s, int i)
{
	return (s[i] == '2' && s[i + 1] == '>' && s[i + 2] && ft_strncmp(&s[i + 2],
			"/dev/null", 9) == 0);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	skip_spaces(const char *s, int i)
{
	while (s[i] && is_space(s[i]))
		i++;
	return (i);
}
