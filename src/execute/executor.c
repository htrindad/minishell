/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:46:43 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/05 18:59:11 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_child(t_token *token, char **env, int prev_fd, t_ms *ms)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (token->fds)
		if (handle_redirections(token))
			em("Failed.", ms);
	if (token->cchar == PIPE && token->next)
	{
		close(ms->pipefd[0]);
		dup2(ms->pipefd[1], STDOUT_FILENO);
		close(ms->pipefd[1]);
	}
	if (token->value && is_builtin(token->value[0]))
		single_exec(token, ms, false);
	execve(find_command(token->value[0], env, ms), token->value, env);
	perror("execve:");
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

	if (token->cchar == PIPE && token->next)
		if (pipe(ms->pipefd) < 0)
			return (em("Error\nPipe Fail.", ms));
	pid = fork();
	if (pid < 0)
		return (em("Error\nFork Fail.", ms));
	if (!pid)
	{
		exec_child(token, env, *prev_fd, ms);
		ret(ms);
		clean_ms(ms);
		free_args(env);
		exit(127);
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
	while (token)
	{
		next = token->next;
		if (!token->next && !token->fds && token->value
			&& is_builtin(token->value[0]) && prev_fd == -1)
		{
			if (exec_builtin(token, *ms) < 0)
				return ((*ms)->last_status = 0, free_args(env));
		}
		else
			exec_cmd(*ms, token, env, &prev_fd);
		token = next;
	}
	wait_process(*ms);
	free_args(env);
}
