/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underscor_sim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:40:03 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 13:43:25 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_envp_underscore(t_user_info *user, const char *last_arg)
{
	user->envp = ms_setenv(user->envp, "_", last_arg);
}

static void	add_underscore_to_env_list(t_user_info *user, t_list *prev,
		const char *last_arg)
{
	t_list	*new_node;

	new_node = ft_lstnew(ft_strjoin("_=", last_arg));
	if (new_node)
	{
		if (prev)
			prev->next = new_node;
		else
			user->env = new_node;
	}
}

static void	update_env_list_underscore(t_user_info *user, const char *last_arg)
{
	t_list	*current;
	t_list	*prev;
	char	*env_str;

	current = user->env;
	prev = NULL;
	while (current)
	{
		env_str = (char *)current->content;
		if (env_str && ft_strncmp(env_str, "_=", 2) == 0)
		{
			free(current->content);
			current->content = ft_strjoin("_=", last_arg);
			return ;
		}
		prev = current;
		current = current->next;
	}
	add_underscore_to_env_list(user, prev, last_arg);
}

static char	*get_last_arg(t_ast *node)
{
	int	i;

	i = 0;
	if (!node || !node->full_cmd || !node->full_cmd[0])
		return (NULL);
	while (node->full_cmd[i])
		i++;
	if (i > 0)
		return (node->full_cmd[i - 1]);
	return (NULL);
}

void	update_underscore_var_s(t_user_info *user, t_ast *node)
{
	char	*last_arg;

	last_arg = get_last_arg(node);
	if (!last_arg)
		return ;
	update_envp_underscore(user, last_arg);
	if (user->env)
		update_env_list_underscore(user, last_arg);
}
