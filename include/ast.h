/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:15:02 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 18:53:21 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "command.h"
# include "token.h"

typedef struct s_ast
{
	t_enum_cmd		type;
	char			**argv;
	char			*infile;
	char			*outfile;
	int				append_mode;
	int				stderr_to_devnull;
	char			*heredoc_delimiter;
	pid_t			child;
	char			**full_cmd;
	char			*ful_path;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct s_expand_ctx
{
	char			**env;
	int				exit_status;
}					t_expand_ctx;

typedef struct s_parse_word_ctx
{
	const char		*s;
	int				i;
	t_token			*token;
	t_expand_ctx	expand_ctx;
}					t_parse_word_ctx;

typedef struct s_match_ctx
{
	const char		*pattern;
	const char		*dir;
	char			**matches;
	int				*count;
}					t_match_ctx;

#endif