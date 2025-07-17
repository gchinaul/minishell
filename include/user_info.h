/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_info.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:22:47 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 11:42:28 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_INFO_H
# define USER_INFO_H

# include <list.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

/*====================================POSIX===================================*/

typedef struct s_cleanup_context
{
	t_list				**tokens;
	struct s_ast		*ast_root;
}						t_cleanup_context;

typedef struct s_user_info
{
	unsigned int		uid;
	unsigned int		euid;
	unsigned int		gid;
	unsigned int		egid;
	char				*user_name;
	int					last_exit_code;
	char				*shell;
	char				*home_dir;
	pid_t				pid;
	t_list				*cmds;
	t_list				*content;
	char				**envp;
	t_list				*env;
	char				**full_cmd;
	t_cleanup_context	*cleanup_ctx;
}						t_user_info;

#endif