/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:48:02 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/14 17:16:14 by mely-pan         ###   ########.fr       */
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
			return (free(line), em("Malloc Failed.", ms), false);
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
			break ;
		}
		tmp = line;
		line = ft_strjoin(tmp, "\n");
		free(tmp);
		if (!line)
			return (em("Malloc Failed", ms));
		if (is_delimiter(line, delimiter, r, ms))
			break ;
		write_line_heredoc(line, write_fd, ms, r->heredoc_q);
		free(line);
	}
}

static int	heredoc_parent(int *pipefd, t_ms *ms, struct sigaction *old_act)
{
	int	status;

	status = 0;
	close(pipefd[1]);
	waitpid(-1, &status, 0);
	sigaction(SIGINT, old_act, NULL);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		ms->last_status = 130;
		close(pipefd[0]);
		return (-1);
	}
	return (pipefd[0]);
}

int	handle_heredoc(t_redir *redir, t_ms *ms)
{
	int					pipefd[2];
	pid_t				pid;
	struct sigaction	old_act;

	if (pipe(pipefd) < 0)
		return (perror("heredoc"), -1);
	set_sig(&old_act);
	pid = fork();
	if (pid < 0)
		return (perror("heredoc fork"), -1);
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		close(pipefd[0]);
		do_heredoc(redir->filename, pipefd[1], ms, redir);
		close(pipefd[1]);
		exit(0);
	}
	return (heredoc_parent(pipefd, ms, &old_act));
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
						return (ft_putchar_fd('\n', 1), 1);
					tmp->heredoc_fd = fd;
				}
				tmp = tmp->next;
			}
		}
		token = token->next;
	}
	return (0);
}
