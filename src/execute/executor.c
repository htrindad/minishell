/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:46:43 by htrindad          #+#    #+#             */
/*   Updated: 2025/05/30 21:00:27 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_child(t_token *token, char **env, int prev_fd, t_ms *ms)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (token->fds)
		if (handle_redirections(token))
			return (em("Failed.", ms));
	if (token->cchar == PIPE && token->next)
	{
		close(ms->pipefd[0]);
		dup2(ms->pipefd[1], STDOUT_FILENO);
		close(ms->pipefd[1]);
	}
	if (token->value && is_builtin(token->value[0]))
		exit(single_exec(token, ms, true));
	execve(find_command(token->value[0], env, ms), token->value, env);
	perror("execve:");
	exit(0);
}

static void	handle_parent(t_ms *ms, t_token *token, int *prev_fd)
{
	int	status;

	refresh(ms->pid);
	if (waitpid(ms->pid, &status, 0) == -1)
		ms->last_status = 1;
	else if (WIFEXITED(status))
		ms->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ms->last_status = WTERMSIG(status) + 128;
	else
		ms->last_status = 1;
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
		exec_child(token, env, *prev_fd, ms);
	else
	{
		ms->pid = pid;
		handle_parent(ms, token, prev_fd);
	}
}

//This is the function that will execute the commands from the parsing
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
	{
		em("Error\nMalloc Fail.\n", (*ms));
		return ;
	}
	while (token)
	{
		next = token->next;
		if (!token->next && !token->fds && token->value
			&& is_builtin(token->value[0]))
			if (exec_builtin(token, *ms, env) < 0)
				return ((*ms)->last_status = 0, free_args(env));
		else
			exec_cmd(*ms, token, env, &prev_fd);
		token = next;
	}
	free_args(env);
}
