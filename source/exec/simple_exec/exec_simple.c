/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 09:25:41 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 13:02:19 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	restore_std_fds(int saved_stdin, int saved_stdout, int saved_stderr)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	if (saved_stderr != -1)
	{
		dup2(saved_stderr, STDERR_FILENO);
		close(saved_stderr);
	}
	return (0);
}

static int	exec_builtin_with_redir(t_ast *node, t_user_info *user, int *exiter)
{
	t_list	dummy;
	int		saved_stdin;
	int		saved_stdout;
	int		saved_stderr;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	saved_stderr = dup(STDERR_FILENO);
	dummy.content = node;
	dummy.next = NULL;
	if (handle_redirections_safe(node, user->envp) != 0)
	{
		restore_std_fds(saved_stdin, saved_stdout, saved_stderr);
		user->last_exit_code = 1;
		return (1);
	}
	ms_builtin(user, &dummy, exiter);
	restore_std_fds(saved_stdin, saved_stdout, saved_stderr);
	return (user->last_exit_code);
}

static int	exec_builtin_no_redir(t_ast *node, t_user_info *user, int *exiter)
{
	t_list	dummy;

	dummy.content = node;
	dummy.next = NULL;
	ms_builtin(user, &dummy, exiter);
	return (user->last_exit_code);
}

static int	exec_external_cmd(t_ast *node, t_user_info *user, int *exiter)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		handle_child_process_s(node, user);
	user->last_exit_code = wait_for_child_sim(pid, exiter);
	update_underscore_var_s(user, node);
	return (user->last_exit_code);
}

int	execute_simple(t_ast *node, t_user_info *user, int *exiter)
{
	int		is_builtin;
	ssize_t	ret;

	if (!node || !node->full_cmd || !node->full_cmd[0] || !node->full_cmd[0][0])
	{
		if (node && node->full_cmd && node->full_cmd[0]
			&& !node->full_cmd[0][0])
			return (0);
		ret = write(STDERR_FILENO, "minishell: invalid command node\n", 32);
		(void)ret;
		return (127);
	}
	is_builtin = is_builtin_command(node->full_cmd[0]);
	if (is_builtin)
	{
		if (node->infile || node->outfile || node->heredoc_delimiter
			|| node->stderr_to_devnull)
			return (exec_builtin_with_redir(node, user, exiter));
		else
			return (exec_builtin_no_redir(node, user, exiter));
	}
	return (exec_external_cmd(node, user, exiter));
}
