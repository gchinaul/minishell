/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chartype.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:21:03 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 15:21:25 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_ctype_ok(int c)
{
	return (c >= 0 && c <= CHAR_MAX);
}

int	ft_isspace(int c)
{
	return ((c) == ' ' || (c) == '\t' || (c) == '\n' || (c) == '\r'
		|| (c) == '\v' || (c) == '\f');
}

int	ft_operator(int c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	ft_quote(int c)
{
	return (c == '\'' || c == '\"');
}
