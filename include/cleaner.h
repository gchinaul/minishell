/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:17:23 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 22:52:14 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANER_H
# define CLEANER_H

# include "ast.h"
# include "list.h"

typedef struct s_copy_ctx
{
	const char	*input;
	int			i;
	char		*output;
	int			j;
	int			in_word;
	int			in_single_quote;
	int			in_double_quote;
}				t_copy_ctx;

/* Free functions */
void			free_tokens(t_list **tokens);
void			free_ast(t_ast *node);

/* Input cleaner */
char			*ft_input_cleaner(char *input);
void			handle_quote_state_c(t_copy_ctx *ctx, char c);
void			copy_char_c(t_copy_ctx *ctx, char c);
void			handle_space_state_c(t_copy_ctx *ctx, char c);

#endif