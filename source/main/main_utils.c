/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:13:36 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 11:42:27 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_user_info_m(t_user_info *user, char **envp)
{
	user->envp = ms_env_init(envp);
	user->env = ms_env_list_init(user->envp);
	user->last_exit_code = 0;
	user->cleanup_ctx = NULL;
}

void	cleanup_user_info_m(t_user_info *user)
{
	ft_free_matrix(&user->envp);
	ft_lstclear(&user->env, free);
}
