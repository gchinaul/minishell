/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:30:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/27 19:29:13 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_dir(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			return (ft_strdup(&env[i][5]));
		i++;
	}
	return (ft_strdup("/"));
}

char	*expand_tilde(const char *s, int *i, char **env)
{
	if (s[*i] != '~')
		return (ft_strdup(""));
	(*i)++;
	if (!s[*i] || s[*i] == ' ' || s[*i] == '\t' || s[*i] == '/')
		return (get_home_dir(env));
	return (ft_strdup("~"));
}
