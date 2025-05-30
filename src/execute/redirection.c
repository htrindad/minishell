/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:34:14 by mely-pan          #+#    #+#             */
/*   Updated: 2025/05/26 20:11:34 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_redir(t_redir **redir_list, t_case type, char *filename)
{
	t_redir *tmp;
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return (1);
	new->filename = ft_strdup(filename);
	if (!new->filename)
		return (free(new), 1);
	new->type = type;
	new->next = NULL;
	if (!*redir_list)
		*redir_list = new;
	else
	{
		tmp = *redir_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

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

bool	is_redirection(t_case type)
{
	if (type != NONE && type != PIPE)
		return (true);
	return (false);
}

static int	set_redir(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp && is_redirection(tmp->cchar))
	{
		if (tok->cchar == IN || tok->cchar == HEREDOC)
		{
			if (tmp->next && tmp->next->value && add_redir(&tok->fds->in, tmp->cchar, tmp->next->value[0]))
				return (1);
		}
		else
		{
			if (tmp->next && tmp->next->value && add_redir(&tok->fds->out, tmp->cchar, tmp->next->value[0]))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	parse_redirections(t_token **tokens)
{
	t_token	*curr;

	curr = *tokens;
	if (DEBUG)
		print_tokens(*tokens);
	while (curr)
	{
		if (curr && is_redirection(curr->cchar) && curr->is_redir == false)
		{
			if (!curr->next || !curr->next->value || !curr->next->value[0])
				return (1);
			if (!curr->fds)
			{
				curr->fds = ft_calloc(1, sizeof(t_fds));
				if (!curr->fds)
					return (1);
				curr->fds->in = NULL;
				curr->fds->out = NULL;
			}
			if (set_redir(curr))
				return (1);
			while (curr->next && is_redirection(curr->next->cchar))
			{
				curr->next->is_redir = true;
				curr->next->fds = NULL;
				curr = curr->next;
			}
		}
		else
			curr->fds = NULL;
		if (curr)
			curr = curr->next;
	}
	cleanup_redir(tokens);
	if (DEBUG)
		print_tokens_debug(*tokens);
	return (0);
}
