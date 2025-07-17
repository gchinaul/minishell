/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:45:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 22:50:17 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "ast.h"
# include "user_info.h"
# include <sys/types.h>

/* Main execution */
int		execute_ast(t_ast *node, t_user_info *user, int *exiter);
int		execute_simple(t_ast *node, t_user_info *user, int *exiter);
int		execute_pipe(t_ast *node, t_user_info *user, int *exiter);

/* Command path resolution */
char	*find_command_path(char *cmd, char **envp);
char	*resolve_command_path(const char *cmd, char **env);
char	*find_command_in_path(const char *cmd, char **env);
char	*build_full_path_path(const char *dir, const char *cmd);

/* File and directory checks */
int		file_exists_path(const char *path);
int		is_executable_file_path(const char *path);
int		is_executable(const char *path);
int		is_directory(const char *path);
int		is_builtin_command(const char *cmd);

/* Process management */
pid_t	fork_and_exec_left(t_ast *left, int pipefd[2], t_user_info *user,
			int *exiter);
pid_t	fork_and_exec_right(t_ast *right, int pipefd[2], t_user_info *user,
			int *exiter);
int		wait_for_child_sim(pid_t pid, int *exiter);
int		handle_child_process_s(t_ast *node, t_user_info *user);

/* Pipe utilities */
int		create_pipe_1(int pipefd[2]);

/* Memory and cleanup */
void	cleanup_child_memory_1(t_user_info *user);
void	cleanup_child_memory_sim(t_user_info *user);

/* Environment updates */
void	update_underscore_in_pipeline_1(t_user_info *us, t_ast *left_node);
void	update_underscore_var_s(t_user_info *user, t_ast *node);

/* Error handling */
void	handle_cmd_path_errors_s(const char *cmd_path, const char *cmd_name,
			t_user_info *user);
void	handle_permission_denied(const char *cmd_path, const char *cmd_name,
			t_user_info *user);
void	handle_is_directory(const char *cmd_path, const char *cmd_name,
			t_user_info *user);
void	handle_dot_command(const char *cmd_path, const char *cmd_name,
			t_user_info *user);
void	exit_sim(int code, char *msg, char *to_free, t_user_info *user);
void	print_and_exit_perm(const char *cmd_name, t_user_info *user);
void	print_and_exit_dir(const char *cmd_name, t_user_info *user);

#endif
