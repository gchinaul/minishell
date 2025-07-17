/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:25:50 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 11:42:32 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_interactive_input(void)
{
	return (readline(PROMPT));
}

static char	*read_non_interactive_input(void)
{
	char	buffer[4096];
	int		i;
	char	c;
	ssize_t	bytes_read;

	i = 0;
	while (i < 4095)
	{
		bytes_read = read(STDIN_FILENO, &c, 1);
		if (bytes_read <= 0 || c == '\n')
			break ;
		buffer[i++] = c;
	}
	if (bytes_read <= 0 && i == 0)
		return (NULL);
	buffer[i] = '\0';
	return (ft_strdup(buffer));
}

static char	*get_input(void)
{
	if (isatty(STDIN_FILENO))
		return (read_interactive_input());
	else
		return (read_non_interactive_input());
}

static void	handle_input(char *input, t_user_info *user, int *exiter)
{
	if (*input)
	{
		if (isatty(STDIN_FILENO))
			add_history(input);
		process_input_m(input, user, exiter);
	}
}

int	minishell_loop(char **envp)
{
	char		*input;
	t_user_info	user;
	int			exiter;

	init_user_info_m(&user, envp);
	exiter = 0;
	setup_signals();
	while (1)
	{
		input = get_input();
		if (!input)
		{
			if (isatty(STDIN_FILENO))
				printf("exit\n");
			break ;
		}
		handle_input(input, &user, &exiter);
		free(input);
		if (exiter)
			break ;
	}
	cleanup_user_info_m(&user);
	clear_history();
	rl_clear_history();
	rl_free_line_state();
	rl_cleanup_after_signal();
	return (user.last_exit_code);
}
