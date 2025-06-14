/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 22:01:30 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/14 16:22:14 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_inf(t_redir *redir)
{
	if (redir->type == IN)
		return (open(redir->filename, O_RDONLY));
	else if (redir->type == HEREDOC)
		return (redir->heredoc_fd);
	return (-1);
}

static int	open_outf(t_redir *redir)
{
	if (redir->type == OUT)
		return (open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else
		return (open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644));
}

static int	apply_redir(int fd, int std_fd)
{
	if (fd < 0)
		return (perror("open"), 1);
	if (dup2(fd, std_fd) < 0)
		return (perror("dup2"), close(fd), 1);
	close(fd);
	return (0);
}

int	handle_redirections(t_token *tokens)
{
	t_redir	*redir;
	int		fd;

	redir = tokens->fds->in;
	while (redir)
	{
		fd = open_inf(redir);
		if (fd < 0 || apply_redir(fd, STDIN_FILENO))
			return (1);
		redir = redir->next;
	}
	redir = tokens->fds->out;
	while (redir)
	{
		fd = open_outf(redir);
		if (fd < 0 || apply_redir(fd, STDOUT_FILENO))
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	alloc_fds_if_needed(t_token *curr)
{
	if (!curr->fds)
	{
		curr->fds = ft_calloc(1, sizeof(t_fds));
		if (!curr->fds)
			return (1);
		curr->fds->in = NULL;
		curr->fds->out = NULL;
	}
	return (0);
}
