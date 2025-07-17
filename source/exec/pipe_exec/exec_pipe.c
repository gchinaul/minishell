/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 09:27:38 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 13:33:21 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_fork_error(t_ast *node, int pipefd[2], int is_left)
{
	if (is_left)
		free_ast(node->left);
	else
		free_ast(node->right);
	free_ast(node);
	close(pipefd[0]);
	close(pipefd[1]);
	return (-1);
}

static int	wait_for_children(pid_t pid_left, pid_t pid_right,
		t_user_info *user)
{
	int	status;
	int	exit_status;

	exit_status = 0;
	if (waitpid(pid_left, &status, 0) == -1)
		perror("waitpid");
	if (waitpid(pid_right, &status, 0) == -1)
		perror("waitpid");
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_status = 128 + WTERMSIG(status);
	else
		exit_status = 1;
	user->last_exit_code = exit_status;
	return (exit_status);
}

int	execute_pipe(t_ast *node, t_user_info *user, int *exiter)
{
	int		pipefd[2];
	pid_t	pid_left;
	pid_t	pid_right;

	update_underscore_in_pipeline_1(user, node->left);
	if (create_pipe_1(pipefd) == -1)
		return (-1);
	pid_left = fork_and_exec_left(node->left, pipefd, user, exiter);
	if (pid_left == -1)
		return (handle_fork_error(node, pipefd, 1));
	pid_right = fork_and_exec_right(node->right, pipefd, user, exiter);
	if (pid_right == -1)
		return (handle_fork_error(node, pipefd, 0));
	close(pipefd[0]);
	close(pipefd[1]);
	return (wait_for_children(pid_left, pid_right, user));
}
