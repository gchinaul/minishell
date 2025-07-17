/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:21:14 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 15:18:57 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <list.h>
# include <user_info.h>

typedef enum e_enum_cmd
{
	SIMPLE,
	WORD,
	PIPE,
	AND,
	OR,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	LPAREN,
	RPAREN,
	SUBSHELL,
	CMD_INVALID
}					t_enum_cmd;

typedef int			(*t_builtin_func)(t_user_info *, t_list *, int *);

typedef struct s_builtin
{
	char			*name;
	t_builtin_func	func;
}					t_builtin;

#endif