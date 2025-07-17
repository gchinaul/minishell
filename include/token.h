/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:24:38 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/21 18:12:34 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "list.h"

typedef struct s_token
{
	int		type;
	char	*value;
}			t_token;

typedef struct s_tokenize_context
{
	char	**env;
	t_list	**tokens;
	int		exit_status;
}			t_tokenize_context;

#endif