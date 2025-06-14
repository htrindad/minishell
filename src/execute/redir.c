/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:34:14 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/14 18:01:20 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_redir(t_redir **redir_list, t_case type, char *filename)
{
	t_redir	*tmp;
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return (1);
	new->filename = ft_strdup(filename);
	if (!new->filename)
		return (free(new), 1);
	new->type = type;
	new->heredoc_fd = -1;
	new->heredoc_q = false;
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

bool	is_redirection(t_case type)
{
	if (type != NONE && type != PIPE)
		return (true);
	return (false);
}

static int	set_redir(t_token *tok, char *u_input, int *heredoc_i)
{
	t_token		*tmp;

	tmp = tok;
	while (tmp && is_redirection(tmp->cchar))
	{
		if (tmp->cchar == IN || tmp->cchar == HEREDOC)
		{
			if (tmp->next && tmp->next->value && add_redir(&tok->fds->in,
					tmp->cchar, tmp->next->value[0]))
				return (1);
		}
		else
		{
			if (tmp->next && tmp->next->value && add_redir(&tok->fds->out,
					tmp->cchar, tmp->next->value[0]))
				return (1);
		}
		if (tmp->cchar == HEREDOC)
			*heredoc_i = get_heredoc_quotes(u_input + *heredoc_i, &tok->fds->in);
		tmp = tmp->next;
	}
	return (0);
}

static void	mark_chained_redirs(t_token **curr)
{
	while ((*curr)->next && is_redirection((*curr)->next->cchar))
	{
		(*curr)->next->is_redir = true;
		(*curr)->next->fds = NULL;
		(*curr) = (*curr)->next;
	}
}

int	parse_redirections(t_token **tokens, char *user_input)
{
	t_token	*curr;
	static int	heredoc_i = 0;

	curr = *tokens;
	while (curr)
	{
		if (is_redirection(curr->cchar) && !curr->is_redir)
		{
			if (!curr->next || !curr->next->value || !curr->next->value[0])
				return (1);
			if (alloc_fds_if_needed(curr))
				return (1);
			if (set_redir(curr, user_input, &heredoc_i))
				return (1);
			mark_chained_redirs(&curr);
		}
		else
			curr->fds = NULL;
		curr = curr->next;
	}
	heredoc_i = 0;
	cleanup_redir(tokens);
	return (0);
}
