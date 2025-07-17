/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_list_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:10:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/25 19:16:36 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ms_env_list_init(char **envp)
{
	t_list	*head;
	t_list	*new_node;
	int		i;

	head = NULL;
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_node = ft_lstnew(ft_strdup(envp[i]));
		if (!new_node || !new_node->content)
		{
			ft_lstclear(&head, free);
			return (NULL);
		}
		ft_lstadd_back(&head, new_node);
		i++;
	}
	return (head);
}
