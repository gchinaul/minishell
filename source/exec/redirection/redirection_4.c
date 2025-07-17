/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 09:22:48 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 13:28:43 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input_redir(const char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror(infile);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 (stdin)");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_heredoc_redir(void)
{
	int	fd;

	fd = open("heredoc.tmp", O_RDONLY);
	if (fd < 0)
	{
		perror("open heredoc.tmp");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 heredoc");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_output_redir(const char *outfile, int type)
{
	int	fd;
	int	flags;

	if (type == REDIR_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(outfile, flags, 0644);
	if (fd == -1)
	{
		perror(outfile);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 (stdout)");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
