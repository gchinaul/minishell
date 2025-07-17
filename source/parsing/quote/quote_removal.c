/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:00:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 17:39:14 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_outer_quotes(const char *str)
{
	int		len;
	char	*result;

	if (!str || !*str)
		return (ft_strdup(""));
	len = ft_strlen(str);
	if (len < 2)
		return (ft_strdup(str));
	if ((str[0] == '\'' || str[0] == '"') && str[0] == str[len - 1])
	{
		result = malloc(len - 1);
		if (!result)
			return (NULL);
		ft_strncpy(result, str + 1, len - 2);
		result[len - 2] = '\0';
		return (result);
	}
	return (ft_strdup(str));
}

static void	free_processed_args(char **processed, int last)
{
	while (--last >= 0)
		free(processed[last]);
	free(processed);
}

static int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args && args[count])
		count++;
	return (count);
}

static char	**alloc_processed(int count)
{
	char	**processed;

	processed = malloc(sizeof(char *) * (count + 1));
	if (processed)
		processed[count] = NULL;
	return (processed);
}

char	**process_quotes_in_args(char **args)
{
	char	**processed;
	int		i;
	int		count;

	if (!args)
		return (NULL);
	count = count_args(args);
	processed = alloc_processed(count);
	if (!processed)
		return (NULL);
	i = 0;
	while (i < count)
	{
		processed[i] = remove_outer_quotes(args[i]);
		if (!processed[i])
		{
			free_processed_args(processed, i);
			return (NULL);
		}
		i++;
	}
	return (processed);
}
