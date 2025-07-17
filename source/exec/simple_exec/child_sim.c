/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:44:51 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 11:03:26 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**duplicate_str_array(char **src)
{
	int		i;
	char	**dst;

	i = 0;
	while (src[i])
		i++;
	dst = malloc(sizeof(char *) * (i + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			while (--i >= 0)
				free(dst[i]);
			free(dst);
			return (NULL);
		}
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

static void	exec_child_command(char *cmd_path, char **cmd_argv, char **cmd_envp,
		t_user_info *user)
{
	cleanup_child_memory_sim(user);
	execve(cmd_path, cmd_argv, cmd_envp);
	perror("execve");
	ft_free_matrix(&cmd_argv);
	ft_free_matrix(&cmd_envp);
	free(cmd_path);
	exit(126);
}

static void	prepare_child_execution(t_ast *node, t_user_info *user,
		char **cmd_path, char **cmd_name)
{
	*cmd_name = ft_strdup(node->full_cmd[0]);
	if (!*cmd_name)
		exit_sim(1, NULL, NULL, user);
	handle_redirections(node, user->envp);
	*cmd_path = find_command_path(*cmd_name, user->envp);
	if (!*cmd_path)
	{
		print_command_not_found(*cmd_name);
		exit_sim(127, NULL, *cmd_name, user);
	}
	handle_cmd_path_errors_s(*cmd_path, *cmd_name, user);
}

static void	execute_with_arrays(char *cmd_path, char **cmd_argv,
		char **cmd_envp, t_user_info *user)
{
	if (!cmd_argv)
		exit_sim(126, NULL, cmd_path, user);
	if (!cmd_envp)
	{
		ft_free_matrix(&cmd_argv);
		exit_sim(126, NULL, cmd_path, user);
	}
	exec_child_command(cmd_path, cmd_argv, cmd_envp, user);
}

int	handle_child_process_s(t_ast *node, t_user_info *user)
{
	char	*cmd_path;
	char	**cmd_argv;
	char	**cmd_envp;
	char	*cmd_name;

	prepare_child_execution(node, user, &cmd_path, &cmd_name);
	free(cmd_name);
	cmd_argv = duplicate_str_array(node->full_cmd);
	cmd_envp = duplicate_str_array(user->envp);
	execute_with_arrays(cmd_path, cmd_argv, cmd_envp, user);
	return (0);
}
