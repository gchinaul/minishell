/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:14:15 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 22:53:41 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* System includes */
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/* Project base structures */
# include "ast.h"
# include "command.h"
# include "libft.h"
# include "list.h"
# include "posix.h"
# include "token.h"
# include "user_info.h"

/* Project modules */
# include "builtin.h"
# include "cleaner.h"
# include "env.h"
# include "execution.h"
# include "ms_signal.h"
# include "parsing.h"
# include "redirection.h"
# include "syntax.h"
# include "utils.h"
# include "wildcard.h"

# define PROMPT "minishell> "
# define PATH_MAX 4096
# define ERROR -1
# define SUCCESS 0

extern volatile sig_atomic_t	g_received_signal;

#endif
