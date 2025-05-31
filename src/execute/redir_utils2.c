/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 22:01:30 by mely-pan          #+#    #+#             */
/*   Updated: 2025/05/31 22:08:45 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_redirections(t_token *tokens)
{
	t_redir	*redir;
	int		fd;

	redir = tokens->fds->in;
	while (redir)
	{
		if (redir->type == IN)
			fd = open(redir->filename, O_RDONLY);
		else if (redir->type == HEREDOC)
			fd = handle_heredoc(redir->filename);
		if (fd < 0)
			return (perror(redir->filename), 1);
		if (dup2(fd, STDIN_FILENO) < 0)
			return (perror("dup2"), close(fd), 1);
		close(fd);
		redir = redir->next;
	}
	redir = tokens->fds->out;
	while (redir)
	{
		if (redir->type == OUT)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (perror(redir->filename), 1);
		if (dup2(fd, STDOUT_FILENO) < 0)
			return (perror("dup2"), close(fd), 1);
		close(fd);
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
