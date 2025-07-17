/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:17:17 by gchinaul          #+#    #+#             */
/*   Updated: 2025/06/30 13:18:41 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc_redirection(const char *delimiter, char **env)
{
	int	fd;

	(void)delimiter;
	(void)env;
	fd = open("heredoc.tmp", O_RDONLY);
	if (fd < 0)
	{
		perror("open heredoc.tmp");
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 heredoc");
		close(fd);
		exit(1);
	}
	close(fd);
}

void	handle_input_redirection(t_ast *node, char **env)
{
	int	fd;

	if (node->heredoc_delimiter)
	{
		handle_heredoc_redirection(node->heredoc_delimiter, env);
		return ;
	}
	if (node->infile)
	{
		fd = open(node->infile, O_RDONLY);
		if (fd == -1)
		{
			perror(node->infile);
			exit(1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 (stdin)");
			close(fd);
			exit(1);
		}
		close(fd);
	}
}

void	handle_output_redirection(t_ast *node)
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
			exit(1);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 (stdout)");
			close(fd);
			exit(1);
		}
		close(fd);
	}
}

void	handle_stderr_redirection(t_ast *node)
{
	int	fd;

	if (node->stderr_to_devnull)
	{
		fd = open("/dev/null", O_WRONLY);
		if (fd == -1)
		{
			perror("/dev/null");
			exit(1);
		}
		if (dup2(fd, STDERR_FILENO) == -1)
		{
			perror("dup2 (stderr)");
			close(fd);
			exit(1);
		}
		close(fd);
	}
}

int	handle_redirections_safe(t_ast *node, char **env)
{
	if (handle_input_redirection_safe(node, env) != 0)
		return (1);
	if (handle_output_redirection_safe(node) != 0)
		return (1);
	if (handle_stderr_redirection_safe(node) != 0)
		return (1);
	return (0);
}
