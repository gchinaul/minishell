/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:45:00 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 22:50:16 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "list.h"

/* Syntax checking */
int		check_parentheses(t_list *tokens);
int		check_operators(t_list *tokens);
int		checker_syntax(t_list *tokens);
int		validate_syntax(t_list *tokens);
int		is_empty_parentheses(t_list *curr);
int		pipe_syntax_error(const char *msg);

/* Error printing */
void	print_syntax_error(const char *token);
void	print_command_not_found(const char *cmd);
void	print_permission_denied(const char *cmd);
void	print_no_such_file(const char *file);

#endif
