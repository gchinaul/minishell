/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:34:52 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 11:46:12 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_child_memory_sim(t_user_info *user)
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

int	is_builtin_command(const char *cmd)
{
	static const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit", NULL};
	int					i;

	if (!cmd)
		return (0);
	i = 0;
	while (builtins[i] != NULL)
	{
		if (!ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i]) + 1))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	wait_for_child_sim(pid_t pid, int *exiter)
{
	int	status;
	int	exit_code;

	(void)exiter;
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		exit_code = 1;
	}
	else if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		exit_code = 128 + WTERMSIG(status);
	}
	else
	{
		exit_code = 1;
	}
	return (exit_code);
}
