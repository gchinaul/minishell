/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:04:17 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 17:04:30 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_redirection_operator(const char *s, int i, t_token *token)
{
	int	res;

	res = parse_redir_devnull(s, i, token);
	if (res != i)
		return (res);
	res = parse_redir_out(s, i, token);
	if (res != i)
		return (res);
	res = parse_redir_in(s, i, token);
	return (res);
}
