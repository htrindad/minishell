/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:48:02 by mely-pan          #+#    #+#             */
/*   Updated: 2025/08/11 18:42:28 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_delimiter(char *line, char *delimiter, t_redir *r, t_ms *ms)
{
	char	*expanded;

	if (!line)
		return (false);
	if (r->heredoc_q_type != '\'' && has_env_var(line))
	{
		expanded = handle_env_var(line, ms);
		if (!expanded)
			return (free(line), em("Malloc Failed.", ms, 0), false);
		if (ft_strncmp(expanded, delimiter, ft_strlen(delimiter)) == 0
			&& expanded[ft_strlen(delimiter)] == '\n')
			return (free(line), free(expanded), true);
		free(expanded);
	}
	else if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
		&& line[ft_strlen(delimiter)] == '\n')
		return (free(line), true);
	return (false);
}

static void	do_heredoc(char *delimiter, int write_fd, t_ms *ms, t_redir *r)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			ft_putchar_fd('\n', 1);
			return (em("Readline Failed", ms, 0));
		}
		tmp = line;
		line = ft_strjoin(tmp, "\n");
		free(tmp);
		if (!line)
			return (em("Malloc Failed", ms, 0));
		if (is_delimiter(line, delimiter, r, ms))
			break ;
		write_line_heredoc(line, write_fd, ms, r->heredoc_q);
		free(line);
	}
}

static int	heredoc_parent(int *pipefd, int pid)
{
	int	status;

	status = 0;
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	*in_heredoc() = false;
	if (WEXITSTATUS(status) > 0)
		return (pipefd[0]);
	*es() = 130;
	close(pipefd[0]);
	return (-1);
}

int	handle_heredoc(t_redir *redir, t_ms *ms)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
		return (perror("heredoc"), -1);
	*in_heredoc() = true;
	pid = fork();
	if (pid < 0)
		return (perror("heredoc fork"), -1);
	if (!pid)
	{
		hsh(ms);
		close(pipefd[0]);
		do_heredoc(redir->filename, pipefd[1], ms, redir);
		close(pipefd[1]);
		(ret(ms), clean_ms(ms));
		exit(1);
	}
	ms->pid = pid;
	refresh(ms);
	return (heredoc_parent(pipefd, pid));
}

int	treat_heredocs(t_token *token, t_ms *ms)
{
	t_redir	*tmp;
	int		fd;

	while (token)
	{
		if (token->fds && token->fds->in)
		{
			tmp = token->fds->in;
			while (tmp)
			{
				if (tmp->type == HEREDOC)
				{
					fd = handle_heredoc(tmp, ms);
					if (fd == -1)
						return (close_hds(token), write(1, "\n", 1));
					tmp->heredoc_fd = fd;
				}
				tmp = tmp->next;
			}
		}
		token = token->next;
	}
	return (0);
}
