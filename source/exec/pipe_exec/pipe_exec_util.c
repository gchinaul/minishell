/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:24:11 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 12:29:05 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_child_memory_1(t_user_info *user)
{
	if (user->cleanup_ctx)
	{
		if (user->cleanup_ctx->tokens && *(user->cleanup_ctx->tokens))
			free_tokens(user->cleanup_ctx->tokens);
		if (user->cleanup_ctx->ast_root)
			free_ast(user->cleanup_ctx->ast_root);
	}
	ft_free_matrix(&user->envp);
	ft_lstclear(&user->env, free);
}

int	create_pipe_1(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

void	update_underscore_in_pipeline_1(t_user_info *us, t_ast *left_node)
{
	if (!left_node || !left_node->full_cmd || !left_node->full_cmd[0])
		return ;
	us->envp = ms_setenv(us->envp, "_", left_node->full_cmd[0]);
}
