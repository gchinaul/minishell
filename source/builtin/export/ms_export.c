/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 00:01:19 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 00:09:58 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_no_equal(const char *arg, int *error_code)
{
	(void)arg;
	*error_code = 0;
	return (0);
}

static int	assign_key_val(const char *arg, char **key, char **val)
{
	int	idx;

	idx = ft_strchr_i(arg, '=');
	*key = ft_substr(arg, 0, idx);
	*val = ft_strdup(ft_strchr(arg, '=') + 1);
	if (!*key || !*val)
		return (1);
	return (0);
}

static char	*export_with_equal(char **env, const char *arg, int *error_code)
{
	char	*key;
	char	*val;

	if (assign_key_val(arg, &key, &val))
	{
		*error_code = 1;
		return (NULL);
	}
	env = ms_setenv(env, key, val);
	free(key);
	free(val);
	*error_code = 0;
	return ((char *)env);
}

char	**ms_env_export(char **env, const char *arg, int *error_code)
{
	if (!arg)
	{
		ft_export_list(env);
		*error_code = 0;
		return (env);
	}
	if (!is_valid_identifier_export(arg))
	{
		print_export_error(arg);
		*error_code = 1;
		return (env);
	}
	if (!ft_strchr(arg, '='))
	{
		handle_no_equal(arg, error_code);
		return (env);
	}
	return ((char **)export_with_equal(env, arg, error_code));
}
