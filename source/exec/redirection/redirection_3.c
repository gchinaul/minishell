/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:21:49 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 14:21:35 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc_redirect_2(const t_ast *node)
{
	int	fd;

	(void)node;
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

int	handle_input_redirection_safe(t_ast *node, char **env)
{
	int	fd;

	(void)env;
	if (node->heredoc_delimiter)
		return (handle_heredoc_redirect_2(node));
	if (node->infile)
	{
		fd = open(node->infile, O_RDONLY);
		if (fd == -1)
		{
			perror(node->infile);
			return (1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 (stdin)");
			close(fd);
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	handle_output_redirection_safe(t_ast *node)
{
	int	fd;
	int	flags;

	if (node->outfile)
	{
		if (node->append_mode)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		fd = open(node->outfile, flags, 0644);
		if (fd == -1)
		{
			perror(node->outfile);
			return (1);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 (stdout)");
			close(fd);
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	handle_stderr_redirection_safe(t_ast *node)
{
	int	fd;

	if (node->stderr_to_devnull)
	{
		fd = open("/dev/null", O_WRONLY);
		if (fd == -1)
		{
			perror("/dev/null");
			return (1);
		}
		if (dup2(fd, STDERR_FILENO) == -1)
		{
			perror("dup2 (stderr)");
			close(fd);
			return (1);
		}
		close(fd);
	}
	return (0);
}

void	handle_redirections(t_ast *node, char **env)
{
	handle_input_redirection_safe(node, env);
	handle_output_redirection_safe(node);
	handle_stderr_redirection_safe(node);
}
