/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_par_word2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:06:07 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 17:06:43 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_char_to_value(char **value, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	*value = ft_strjoin_free(*value, tmp);
	if (*value == NULL)
		return (-1);
	return (0);
}

int	ensure_value_initialized(char **value, int old_len)
{
	(void)old_len;
	if (!*value)
	{
		*value = ft_strdup("");
		if (!*value)
			return (-1);
	}
	return (0);
}

int	handle_single_quote_content(const char *s, int *i, char **value)
{
	while (s[*i] && s[*i] != '\'')
	{
		if (append_char_to_value(value, s[*i]) < 0)
			return (-1);
		(*i)++;
	}
	if (s[*i] != '\'')
	{
		printf("Syntax error: unclosed single quote\n");
		return (-1);
	}
	return (0);
}

int	handle_single_quote(const char *s, int *i, char **value)
{
	int	start_len;

	(*i)++;
	if (*value)
		start_len = (int)strlen(*value);
	else
		start_len = 0;
	if (handle_single_quote_content(s, i, value) < 0)
		return (-1);
	(*i)++;
	return (ensure_value_initialized(value, start_len));
}
