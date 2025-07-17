/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:45:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 22:50:14 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "list.h"
# include "user_info.h"

/* Built-in commands */
int		handle_builtin_exit(char **args, int argc, char **envp, int *exiter);
int		handle_builtin_export(t_user_info *prompt, char **args);
int		handle_builtin_unset(t_user_info *prompt, char **args);
int		ms_builtin(t_user_info *prompt, t_list *cmd, int *exiter);
int		ms_echo(t_list *cmd);
int		ms_pwd(void);
int		ms_cd(char **args, char ***env);
int		ms_exit(int argc, char **argv, char **envp);
int		ms_env(char **env);

/* Built-in wrappers */
int		ms_cd_wrapper(t_user_info *prompt, t_list *cmd, int *exiter);
int		ms_env_export_wrapper(t_user_info *prompt, t_list *cmd,
			int *error_code);
int		ms_unsetenv_wrapper(t_user_info *prompt, t_list *cmd, int *exiter);
int		ms_env_wrapper(t_user_info *prompt, t_list *cmd, int *exiter);
int		ms_exit_wrapper(t_user_info *prompt, t_list *cmd, int *exiter);
int		ms_echo_wrapper(t_user_info *prompt, t_list *cmd, int *exiter);
int		ms_pwd_wrapper(t_user_info *prompt, t_list *cmd, int *exiter);

/* Built-in utilities */
char	*get_target_directory(char **args, char **env);
int		update_env_pwd(char ***env, char *oldpwd);
void	ft_export_list(char **env);
void	print_export_error(const char *arg);
int		is_valid_identifier_export(const char *str);
int		handle_export_args_2(char ***envp, char **args);
int		handle_export_arg(char ***envp, const char *arg);
void	free_new_env(char **new_env, int j);
void	substitute_env_vars(char **args, char **env);

#endif
