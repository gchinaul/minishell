/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:45:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 22:50:15 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "list.h"

/* Environment management */
int		ms_is_valid_var_char(char c);
int		ms_is_valid_var_name(char *s);
char	*ms_getenv(char **env, const char *key, int n);
char	**ms_env_add(char **env, char *entry);
char	**ms_setenv(char **env, const char *key, const char *value);
char	**ms_env_init(char **envp);
t_list	*ms_env_list_init(char **envp);
char	**ms_unsetenv(char **env, const char *key);
char	**ms_env_export(char **env, const char *arg, int *error_code);
char	*get_env_var(const char *name, char **env);

#endif
