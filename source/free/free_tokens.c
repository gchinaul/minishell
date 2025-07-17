/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 09:58:02 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/25 20:43:21 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_token(void *content)
{
	t_token	*token;

	if (!content)
		return ;
	token = (t_token *)content;
	if (token->value)
		free(token->value);
	free(token);
}

void	free_tokens(t_list **tokens)
{
	if (!tokens || !*tokens)
		return ;
	ft_lstclear(tokens, del_token);
}
