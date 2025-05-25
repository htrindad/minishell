/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:10:16 by htrindad          #+#    #+#             */
/*   Updated: 2025/05/25 19:19:12 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fd_checker(t_token *token)
{
	if (token != NULL && token->fds != NULL \
			&& token->value != NULL)
	{
		if (token->fds->in && token->fds->in->filename)
		{
			if (!ft_strncmp(token->fds->in->filename, token->value[0], ft_strlen(token->value[0])))
				if (token->value[1])
					return (1);
		}
		else if (token->fds->out && token->fds->out->filename)
			if (!ft_strncmp(token->fds->out->filename, token->value[0], ft_strlen(token->value[0])))
				if (token->value[1])
					return (1);
	}
	return (0);
}

static int	bi_redirections(t_token **tokens, t_ms *ms)
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
		single_exec(*tokens, ms, false);
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
		single_exec(*tokens, ms, false);
		close(fd);
		redir = redir->next;
	}
	return (0);
}

int	single_exec(t_token *token, t_ms *ms, bool is_parent)
{
	size_t	i;
	int		arg;

	i = 0;
	arg = fd_checker(token);
	while (ms->builtin[i].name)
	{
		if (token->value[arg] && ms->builtin[i].name
			&& !ft_strncmp(token->value[arg], ms->builtin[i].name,
				ft_strlen(ms->builtin[i].name) + 1))
		{
			if(is_parent && token->value && is_builtin(token->value[arg]))
				return (ms->builtin[i].f(ms), 0);
			else if (!is_parent)
				exit(ms->builtin[i].f(ms));
		}
		i++;
	}
	return (-1);
}

int	redir_exec(t_token *token, t_ms *ms)
{
	char	**env;

	env = comp_env(ms->env);
	if (env == NULL)
		return (em("Error\nMalloc Fail.", ms), -1);
	if (token->fds)
	{
		if (bi_redirections(&token, ms))
			return (em("Failed.", ms), -1);
	}
	else
		single_exec(token, ms, true);
	exit(0);
	return (0);
}
