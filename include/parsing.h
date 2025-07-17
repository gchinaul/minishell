/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:45:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 22:50:15 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "ast.h"
# include "list.h"
# include "token.h"

/* Tokenization */
int		tokenize(const char *input, t_list **tokens, char **env,
			int exit_status);
int		is_space(char c);
int		is_operator(char c);
int		is_digit_redirection(const char *s, int i);
int		is_quote(char c);

/* Token utilities */
t_token	*alloc_token(void);
int		process_token(char *cleaned, int i, t_tokenize_context *ctx,
			int *new_index);
int		tokenize_loop_t(char *cleaned, t_tokenize_context *ctx);

/* Token parsing */
int		parse_operator_t(const char *s, int i, t_token *token);
int		parse_pipe_paren_operator(const char *s, int i, t_token *token);
int		parse_redir_in(const char *s, int i, t_token *token);
int		parse_double_operator(const char *s, int i, t_token *token);
int		parse_redir_devnull(const char *s, int i, t_token *token);
int		parse_redir_out(const char *s, int i, t_token *token);
int		parse_redirection_operator(const char *s, int i, t_token *token);
int		parse_single_operator(const char *s, int i, t_token *token);

/* Expansion */
char	*expand_variable(const char *str, int *i, char **env, int exit_status);
char	*expand_variable_in_dquotes(const char *str, int *i, char **env,
			int exit_status);
char	*expand_variable_improved(const char *str, int *pos, char **env,
			int exit_status);
char	*expand_tilde(const char *str, int *i, char **env);
char	*remove_quotes_and_expand(const char *input, char **env);
int		skip_spaces(const char *s, int i);

/* Quote handling */
int		handle_single_quote(const char *s, int *i, char **value);
int		handle_single_quote_content(const char *s, int *i, char **value);
int		handle_double_quote(const char *s, int *i, char **value,
			t_expand_ctx *ctx);
int		handle_double_quote_content_ctx(const char *s, int *i, char **value,
			t_expand_ctx *ctx);
int		handle_double_quote_ctx(const char *s, int *i, char **value,
			t_expand_ctx *ctx);
int		handle_double_quote_expansion(const char *s, int *i, char **value,
			t_expand_ctx *ctx);

/* Variable expansion */
int		handle_dollar(const char *s, int *i, char **value, t_expand_ctx *ctx);
int		handle_tilde(const char *s, int *i, char **value, t_expand_ctx *ctx);
int		handle_dollar_ctx(const char *s, int *i, char **value,
			t_expand_ctx *ctx);
int		handle_tilde_ctx(const char *s, int *i, char **value,
			t_expand_ctx *ctx);
int		handle_dollar_in_dquotes(const char *s, int *i, char **value,
			t_expand_ctx *ctx);
int		handle_exit_status(char **value, int *i, t_expand_ctx *ctx);
int		append_expanded_variable_ctx(const char *s, int *i, char **value,
			t_expand_ctx *ctx);

/* Parsing utilities */
int		parse_word_ctx(t_parse_word_ctx *ctx);
int		append_char_to_value(char **value, char c);
int		ensure_value_initialized(char **value, int old_len);
char	*get_var_name_v(const char *s, int *i);
char	*get_env_value_v(const char *name, char **env, int exit_status);

/* AST parsing */
t_ast	*new_ast_node(t_enum_cmd type);
t_ast	*parse_command(t_list *tokens);
t_ast	*parse_command_recursive(t_list *tokens);
t_ast	*parse_logical_command(t_list *tokens);
t_ast	*parse_simple_command(t_list **tokens);

/* AST utilities */
t_token	*duplicate_token(t_token *token);
int		find_last_pipe(t_list *tokens);
int		find_last_logical_operator(t_list *tokens);
int		find_last_l_oper_with_paren(t_list *tokens);
void	split_token(t_list *tokens, int index, t_list **left, t_list **right);

/* Command filling */
void	fill_cmd_argv(t_ast *node, t_list *tokens);
int		fill_cmd_redir(t_ast *node, t_list *tokens);
void	fill_simple_cmd(t_ast *node, t_list *tokens);
int		count_cmd_args_b(t_list *tokens);
void	fill_cmd_args_b(t_ast *node, t_list *tokens, int count);
int		fill_args_loop_b(char ***argv, t_list *tokens, int *arg_count,
			int *capacity);
int		process_token_b(char ***argv, int *capacity, int *arg_count,
			t_token *tok);
void	free_argv_on_error_b(char **argv, int arg_count);

/* Argument expansion */
int		add_expanded_args(char ***argv_ptr, int *capacity, int *count,
			const char *token_value);
int		ensure_argv_capacity(char ***argv_ptr, int *capacity, int needed);
void	add_expanded_to_argv(char ***argv_ptr, int *count, char **expanded);

/* Duplication utilities */
t_list	*duplicate_token_list(t_list *tokens);

#endif
