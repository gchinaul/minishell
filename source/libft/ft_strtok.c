/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:30:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 13:15:08 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_delimiter(char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

char	*ft_strtok(char *str, const char *delim, char **saveptr)
{
	char	*start;

	if (str != NULL)
		*saveptr = str;
	if (*saveptr == NULL)
		return (NULL);
	while (**saveptr && is_delimiter(**saveptr, delim))
		(*saveptr)++;
	if (**saveptr == '\0')
	{
		*saveptr = NULL;
		return (NULL);
	}
	start = *saveptr;
	while (**saveptr && !is_delimiter(**saveptr, delim))
		(*saveptr)++;
	if (**saveptr)
	{
		**saveptr = '\0';
		(*saveptr)++;
	}
	else
		*saveptr = NULL;
	return (start);
}
