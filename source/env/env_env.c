/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 21:22:29 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/16 21:36:15 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_is_valid_var_char(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
			&& c <= '9') || (c == '_'));
}

int	ms_is_valid_var_name(char *s)
{
	if (!s || (*s >= '0' && *s <= '9') || !ms_is_valid_var_char(*s++))
		return (0);
	while (ms_is_valid_var_char(*s))
		s++;
	return (*s == '=');
}
