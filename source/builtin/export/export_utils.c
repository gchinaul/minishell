/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 23:53:57 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 00:11:11 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_list(char **env)
{
	int		i;
	char	*entry;
	ssize_t	ret;

	if (!env)
	{
		return ;
	}
	i = 0;
	while (env[i])
	{
		entry = env[i];
		if (!entry)
		{
			return ;
		}
		ret = write(STDOUT_FILENO, "declare -x ", 11);
		(void)ret;
		ret = write(STDOUT_FILENO, entry, ft_strlen(entry));
		(void)ret;
		ret = write(STDOUT_FILENO, "\n", 1);
		(void)ret;
		i++;
	}
}

void	print_export_error(const char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

int	is_valid_identifier_export(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')
			|| str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
					&& str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	handle_export_args_2(char ***envp, char **args)
{
	int	overall_error;
	int	i;

	overall_error = 0;
	i = 1;
	while (args[i])
	{
		if (handle_export_arg(envp, args[i]))
			overall_error = 1;
		i++;
	}
	return (overall_error);
}
