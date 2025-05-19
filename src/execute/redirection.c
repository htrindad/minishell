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

int	handle_redirections(t_token **tokens)
{
	t_redir	*redir;
	int		fd;

	redir = (*tokens)->fds->in;
	while (redir)
	{
		fd = open(redir->filename, O_RDONLY);
		if (fd < 0)
			return (perror(redir->filename), 1);
		if (dup2(fd, STDIN_FILENO) < 0)
			return (perror("dup2"), close(fd), 1);
		close(fd);
		redir = redir->next;
	}
	redir = (*tokens)->fds->out;
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
	if (type == APPEND || type == IN || type == OUT || type == HEREDOC)
		return (true);
	return (false);
}

static int	set_redir(t_token *tok)
{
	if (tok->cchar == IN || tok->cchar == HEREDOC)
	{
		if (add_redir(&tok->fds->in, tok->cchar, tok->next->value[0]))
			return (1);
	}
	else
	{
		if (add_redir(&tok->fds->out, tok->cchar, tok->next->value[0]))
			return (1);
	}
	return (0);
}

int	parse_redirections(t_token **tokens)
{
	t_token	*curr;

	curr = *tokens;
	while (curr)
	{
		if (is_redirection(curr->cchar))
		{
			if (!curr->next || !curr->next->value || !curr->next->value[0])
				return (1);
			if (!curr->fds)
			{
				curr->fds = ft_calloc(1, sizeof(t_fds));
				if (!curr->fds)
					return (1);
			}
			if (set_redir(curr))
				return (1);
		}
		curr = curr->next;
	}
	cleanup_redir(tokens);
	return (0);
}
