/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:45:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 22:50:18 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "ast.h"
# include "list.h"

/* Redirection handling */
void	handle_redirections(t_ast *node, char **env);
int		handle_redirections_safe(t_ast *node, char **env);
int		handle_multiple_redir_safe(t_list *tokens, char **env);

/* Input redirections */
void	handle_input_redirection(t_ast *node, char **env);
int		handle_input_redirection_safe(t_ast *node, char **env);
int		handle_input_redir(const char *infile);

/* Output redirections */
void	handle_output_redirection(t_ast *node);
int		handle_output_redirection_safe(t_ast *node);
int		handle_output_redir(const char *outfile, int type);
void	handle_stderr_redirection(t_ast *node);
int		handle_stderr_redirection_safe(t_ast *node);
void	handle_stderr_devnull(t_ast *node);

/* Heredoc */
void	handle_heredoc_redirection(const char *delim, char **env);
int		handle_heredoc(const char *delimiter, char **env);
int		handle_heredoc_redir(void);
int		prepare_heredocs(t_ast *node, char **env);

/* Redirection utilities */
int		handle_redir_out_r(t_ast *node, t_token *tok, t_list *tmp);
int		open_outfile(char *filename, int flags);
int		check_ambiguous_redirect(char *filename);

#endif
