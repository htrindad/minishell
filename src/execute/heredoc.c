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

static void	do_heredoc(char *delimiter, int write_fd, t_ms *ms)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		expanded = handle_env_var(line, ms);
		if (!expanded)
			return (em("heredoc", ms));
		write(write_fd, expanded, ft_strlen(expanded));
		free(expanded);
		free(line);
	}
	close(write_fd);
}

int	handle_heredoc(char *delimiter, t_ms *ms)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	status = 0;
	if (pipe(pipefd) < 0)
		return (perror("heredoc"), -1);
	pid = fork();
	if (!pid)
		return (do_heredoc(delimiter, pipefd[1], ms), exit(0), 0);
	else
	{
		ms->pid = pid;
		refresh(ms);
		close(pipefd[1]);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			ms->last_status = 130;
			close(pipefd[0]);
			return (-1);
		}
		return (pipefd[0]);
	}
}
