/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 21:43:58 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/16 21:49:39 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_3(const char *s1, const char *s2, const char *s3)
{
	static size_t	len1 = 0;
	static size_t	len2 = 0;
	static size_t	len3 = 0;
	char			*res;

	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	if (s3)
		len3 = ft_strlen(s3);
	res = malloc(sizeof(char) * (len1 + len2 + len3 + 1));
	if (!res)
		return (NULL);
	if (s1)
		ft_strlcpy(res, s1, len1 + 1);
	else
		res[0] = '\0';
	if (s2)
		ft_strlcpy(res + len1, s2, len2 + 1);
	if (s3)
		ft_strlcpy(res + len1 + len2, s3, len3 + 1);
	return (res);
}
