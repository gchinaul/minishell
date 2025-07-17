/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:39:34 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 12:10:53 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*heredoc_readline(const char *prompt)
{
	char	buffer[1024];
	int		i;

	if (isatty(STDIN_FILENO))
		return (readline(prompt));
	else
	{
		i = 0;
		while (i < (int)(sizeof(buffer) - 1))
		{
			if (read(STDIN_FILENO, &buffer[i], 1) <= 0)
				break ;
			if (buffer[i] == '\n')
			{
				buffer[i] = '\0';
				break ;
			}
			i++;
		}
		buffer[i] = '\0';
		if (i == 0)
			return (NULL);
		return (ft_strdup(buffer));
	}
}

static int	heredoc_is_delimiter(const char *line, const char *delimiter)
{
	size_t	len;

	len = ft_strlen(delimiter);
	return (line && ft_strlen(line) == len && ft_strncmp(line, delimiter,
			len) == 0);
}

static void	heredoc_write_line(int fd, const char *line)
{
	ft_putendl_fd(line, fd);
}

int	handle_heredoc(const char *delimiter, char **env)
{
	int		fd;
	char	*line;

	(void)env;
	fd = open("heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	while (1)
	{
		line = heredoc_readline("> ");
		if (!line)
			break ;
		if (heredoc_is_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		heredoc_write_line(fd, line);
		free(line);
	}
	close(fd);
	return (0);
}
