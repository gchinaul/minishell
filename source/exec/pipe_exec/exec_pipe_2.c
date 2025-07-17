/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:26:55 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 12:31:56 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_exec_left(t_ast *left, int pipefd[2], t_user_info *user,
		int *exiter)
{
	int	exit_code;

	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		cleanup_child_memory_1(user);
		exit(1);
	}
	close(pipefd[1]);
	handle_redirections(left, user->envp);
	exit_code = execute_ast(left, user, exiter);
	cleanup_child_memory_1(user);
	exit(exit_code);
}

static void	child_exec_right(t_ast *right, int pipefd[2], t_user_info *user,
		int *exiter)
{
	int	exit_code;

	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		cleanup_child_memory_1(user);
		exit(1);
	}
	close(pipefd[0]);
	handle_redirections(right, user->envp);
	exit_code = execute_ast(right, user, exiter);
	cleanup_child_memory_1(user);
	exit(exit_code);
}

static pid_t	fork_with_error_handling(int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
	}
	return (pid);
}

pid_t	fork_and_exec_left(t_ast *left, int pipefd[2], t_user_info *user,
		int *exiter)
{
	pid_t	pid;

	pid = fork_with_error_handling(pipefd);
	if (pid == 0)
		child_exec_left(left, pipefd, user, exiter);
	return (pid);
}

pid_t	fork_and_exec_right(t_ast *right, int pipefd[2], t_user_info *user,
		int *exiter)
{
	pid_t	pid;

	pid = fork_with_error_handling(pipefd);
	if (pid == 0)
		child_exec_right(right, pipefd, user, exiter);
	return (pid);
}
