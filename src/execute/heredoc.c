/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:48:02 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/07 16:28:19 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	is_delimiter(char *line, char *delimiter)
{
	if (!line)
		return (false);
	if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
		&& line[ft_strlen(delimiter)] == '\n')
		return (free(line), true);
	return (false);
}

static void	do_heredoc(char *delimiter, int write_fd, t_ms *ms)
{
	char	*line;
	char	*expanded;
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
		if (is_delimiter(line, delimiter))
			break ;
		expanded = handle_env_var(line, ms);
		if (!expanded)
			return (free(line), em("heredoc", ms));
		write(write_fd, expanded, ft_strlen(expanded));
		free_two_str(line, expanded);
	}
}

static int	handle_heredoc_parent(int *pipefd, t_ms *ms, int status, struct sigaction *old_act)
{
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
	int					status;
	struct sigaction	old_act;
	struct sigaction	new_act;

	if (pipe(pipefd) < 0)
		return (perror("heredoc"), -1);
	sigaction(SIGINT, NULL, &old_act);
	new_act.sa_handler = SIG_IGN;
	sigemptyset(&new_act.sa_mask);
	new_act.sa_flags = 0;
	sigaction(SIGINT, &new_act, NULL);
	pid = fork();
	if (pid < 0)
		return (perror("heredoc fork"), -1);
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		close(pipefd[0]);
		do_heredoc(redir->filename, pipefd[1], ms);
		close(pipefd[1]);
		exit(0);
	}
	return (handle_heredoc_parent(pipefd, ms, status, &old_act));
}

int	treat_heredocs(t_token *token, t_ms *ms)
{
	t_redir	*tmp;
	int		fd;

	while (token)
	{
		if (token->fds && token->fds->in && token->fds->in->type == HEREDOC)
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
