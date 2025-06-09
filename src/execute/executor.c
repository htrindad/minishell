/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:46:43 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/06 20:48:49 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exec_child(t_token *token, char **env, int prev_fd, t_ms *ms)
{
	int	ec;

	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (token->fds)
		if (handle_redirections(token))
			return (em("Failed.", ms), 1);
	if (token->cchar == PIPE && token->next)
	{
		close(ms->pipefd[0]);
		dup2(ms->pipefd[1], STDOUT_FILENO);
		close(ms->pipefd[1]);
	}
	if (token->value && is_builtin(token->value[0]))
		exit(single_exec(token, ms, false, env));
	return (run_execve(find_command(token->value[0], env, ms), token->value,
			env));
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
	pid_t	pid;
	int		exit_status;

	if (token->cchar == PIPE && token->next)
		if (pipe(ms->pipefd) < 0)
			return (em("Error\nPipe Fail.", ms));
	pid = fork();
	if (pid < 0)
		return (em("Error\nFork Fail.", ms));
	if (!pid)
	{
		exit_status = exec_child(token, env, *prev_fd, ms);
		ret(ms);
		clean_ms(ms);
		free_args(env);
		exit(exit_status);
	}
	else
	{
		ms->pid = pid;
		handle_parent(ms, token, prev_fd);
	}
}

static void	wait_process(t_ms *ms)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (WIFEXITED(status))
			ms->last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ms->last_status = WTERMSIG(status) + 128;
		else
			ms->last_status = 1;
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
	env = comp_env((*ms)->env);
	if (env == NULL)
		return (em("Error\nMalloc Fail.\n", (*ms)));
	if (treat_heredocs(token, *ms))
		return (free_args(env));
	while (token)
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
