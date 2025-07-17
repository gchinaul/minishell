/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:34:49 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 14:13:28 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

# define ERROR 1

# define ERR_LINE_READ "input line read error"
# define ERR_HISTORY "history file recall read error"
# define ERR_CHILD_PROCESS "child process creation error"
# define ERR_NO_CMD "no command found"
# define ERR_NO_PERM "no permission to execute command"
# define ERR_NO_FILE "no such file or directory"
# define ERR_NO_DIR "no such directory"
# define ERR_NO_ENV "no such environment variable"
# define ERR_NO_HOME "no home directory found"
# define ERR_NO_PATH "no path found"
# define ERR_NO_OLDPWD "no OLDPWD environment variable found"
# define ERR_IS_DIR "is a directory"
# define ERR_SIZE_GET_FAIL "size get failed"
# define ERR_TERMIOS "termios error"
# define ERR_NOT_GET_CWD "error not retrieving current working directory"
# define ERR_PIPE "pipe error"
# define ERR_FORK "fork error"
# define ERR_EXECVE "execve error"
# define ERR_SIGNAL "signal error"
# define ERR_MALLOC "malloc error"
# define ERR_NOT_A_DIR "not a directory"
# define ERR_TOO_MANY_ARGS "too many arguments"
# define ERR_TOO_FEW_ARGS "too few arguments"

#endif