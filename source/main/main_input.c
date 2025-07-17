/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:27:13 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 11:42:31 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_comment_line(const char *input)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (input[i] == '#');
}

static int	tokenize_and_check(char *input, t_list **tokens, t_user_info *user)
{
	if (tokenize(input, tokens, user->envp, user->last_exit_code) == 0)
	{
		free_tokens(tokens);
		return (0);
	}
	return (1);
}

static int	handle_empty_or_invalid_tokens(t_list *tokens, t_user_info *user)
{
	if (!tokens)
	{
		user->last_exit_code = 0;
		return (1);
	}
	if (!validate_syntax(tokens))
	{
		user->last_exit_code = 2;
		free_tokens(&tokens);
		return (1);
	}
	return (0);
}

static void	execute_ast_if_ready(t_ast *ast, t_user_info *user, int *exiter)
{
	t_cleanup_context	cleanup_ctx;
	int					exit_code;

	cleanup_ctx.tokens = NULL;
	cleanup_ctx.ast_root = ast;
	user->cleanup_ctx = &cleanup_ctx;
	if (ast)
	{
		if (prepare_heredocs(ast, user->envp) == 0)
		{
			exit_code = execute_ast(ast, user, exiter);
			user->last_exit_code = exit_code;
		}
	}
	free_ast(ast);
}

void	process_input_m(char *input, t_user_info *user, int *exiter)
{
	t_list	*tokens;
	t_ast	*ast;

	tokens = NULL;
	ast = NULL;
	if (is_comment_line(input))
		return ;
	if (!tokenize_and_check(input, &tokens, user))
		return ;
	if (handle_empty_or_invalid_tokens(tokens, user))
		return ;
	ast = parse_command(tokens);
	execute_ast_if_ready(ast, user, exiter);
}
