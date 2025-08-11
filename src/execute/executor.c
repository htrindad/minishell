/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:46:43 by mely-pan          #+#    #+#             */
/*   Updated: 2025/08/11 18:04:56 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exec_child(t_token *token, char **env, int prev_fd, t_ms *ms)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (token->cchar == PIPE && token->next)
	{
		close(ms->pipefd[0]);
		dup2(ms->pipefd[1], STDOUT_FILENO);
		close(ms->pipefd[1]);
	}
	if (token->fds)
		if (handle_redirections(token))
			return (em("Failed.", ms, 0), 1);
	if (token->value && is_builtin(token->value[0]))
		exit(single_exec(token, ms, false, env));
	if (token->value)
		return (run_execve(find_command(token->value[0], env, ms), token->value,
				env, token->value[0]));
	return (0);
}

static void	handle_parent(t_ms *ms, t_token *token, int *prev_fd)
{
	refresh(ms);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (token->cchar == PIPE && token->next)
	{
		close(ms->pipefd[1]);
		*prev_fd = ms->pipefd[0];
	}
}

static void	exec_cmd(t_ms *ms, t_token *token, char **env, int *prev_fd)
{
	pid_t			pid;

	if (token->cchar == PIPE && token->next)
		if (pipe(ms->pipefd) < 0)
			return (em("Error\nPipe Fail.", ms, 0));
	tcgetattr(STDIN_FILENO, &ms->term);
	pid = fork();
	if (pid < 0)
		return (em("Error\nFork Fail.", ms, 0));
	if (!pid)
	{
		*es() = exec_child(token, env, *prev_fd, ms);
		ret(ms);
		clean_ms(ms);
		free_args(env);
		exit(*es());
	}
	else
	{
		ms->pid = pid;
		handle_parent(ms, token, prev_fd);
		tcsetattr(STDIN_FILENO, TCSANOW, &ms->term);
	}
}

static void	wait_process(t_ms *ms)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (ms->pid == pid)
		{
			if (WIFEXITED(status))
				*es() = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				*es() = WTERMSIG(status) + 128;
			else
				*es() = 1;
		}
		pid = waitpid(-1, &status, 0);
	}
}

// This is the function that will execute the commands from the parsing
void	executor(t_ms **ms)
{
	char	**env;
	t_token	*token;
	t_token	*next;
	int		prev_fd;

	token = (*ms)->tokens;
	prev_fd = -1;
	if (treat_heredocs(token, *ms))
		return ;
	env = comp_env((*ms)->env);
	if (env == NULL)
		return (em("Error\nMalloc Fail.\n", (*ms), 0));
	while (token && change_the_score((*ms)->env, (*ms)->tokens))
	{
		next = token->next;
		if (is_single_token_and_builtin(token, prev_fd))
		{
			*es() = exec_builtin(token, *ms);
			return (free_args(env));
		}
		else
			exec_cmd(*ms, token, env, &prev_fd);
		token = next;
	}
	return (wait_process(*ms), free_args(env));
}
