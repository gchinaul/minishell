/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:19:27 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/21 22:19:40 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_itoa(int n)
{
	int				i;
	int				neg;
	unsigned int	num;
	char			buffer[12];

	i = 11;
	neg = (n < 0);
	buffer[11] = '\0';
	if (n == 0)
	{
		buffer[10] = '0';
		return (ft_strdup(&buffer[10]));
	}
	if (neg)
		num = -n;
	else
		num = n;
	while (num > 0)
	{
		buffer[--i] = (num % 10) + '0';
		num /= 10;
	}
	if (neg)
		buffer[--i] = '-';
	return (ft_strdup(&buffer[i]));
}
