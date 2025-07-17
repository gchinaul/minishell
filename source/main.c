/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 09:43:48 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 15:31:02 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_received_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_user_info	user;
	int			exiter;

	if (argc == 1)
		return (minishell_loop(envp));
	if (argc == 3 && ft_strncmp(argv[1], "-c", 3) == 0)
	{
		init_user_info_m(&user, envp);
		exiter = 0;
		setup_signals();
		process_input_m(argv[2], &user, &exiter);
		cleanup_user_info_m(&user);
		return (user.last_exit_code);
	}
	ft_putstr_fd("Usage: ./minishell or ./minishell -c \"command\"\n", 2);
	return (1);
}
