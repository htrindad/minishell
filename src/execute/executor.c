/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:46:43 by htrindad          #+#    #+#             */
/*   Updated: 2025/05/16 19:12:40 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline size_t	envsize(t_env *env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static char	**comp_env(t_env *env)
{
	char	**ptr;
	char	*tmp;
	size_t	i;
	size_t	j;

	i = envsize(env);
	j = 0;
	if (!i)
		return (NULL);
	ptr = ft_calloc(i + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	while (env)
	{
		tmp = ft_calloc(ft_strlen(env->key) + ft_strlen(env->value) + 2, sizeof(char));
		if (tmp == NULL)
			return (free_args(ptr), NULL);
		ft_strlcpy(tmp, env->key, ft_strlen(env->key) + 1);
		ft_strlcat(tmp, "=", ft_strlen(env->key) + 2);
		ft_strlcat(tmp, env->value, ft_strlen(tmp) + ft_strlen(env->value) + 1);
		ptr[j++] = tmp;
		env = env->next;
	}
	ptr[j] = NULL;
	return (ptr);
}

static void exec_child(t_token *token, char **env, int prev_fd, int *pipe_fd, t_ms *ms)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (token->fds) {
		if (handle_redirections(&token))
			return (em("Failed.", ms));
	}
	if (token->cchar == PIPE && token->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (token->value && is_builtin(token->value[0]))
		exit(exec_builtin(token, ms, false));
	if (DEBUG)
		print_tokens(token);
	execve(find_command(token->value[0], env, ms), token->value, env);
	perror("execve:");
	exit(0);
}

static void	exec_cmd(t_ms *ms, t_token *token, char **env, int *prev_fd) //It will run while we have commands
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (token->cchar == PIPE && token->next)
		if (pipe(pipe_fd) < 0)
			return (em("Error\nPipe Fail.\n", ms));
	pid = fork();
	if (pid < 0)
		return (em("Error\nFork Fail.\n", ms));
	if (!pid)
		exec_child(token, env, *prev_fd, pipe_fd, ms);
	else
	{
		ms->pid = pid;
		refresh(ms->pid);
		if (waitpid(ms->pid, &status, 0) == -1)
			ms->last_status = 1;
		else if (WIFEXITED(status))
				ms->last_status = WEXITSTATUS(status);
		else
			ms->last_status = 1;
		if (*prev_fd != -1)
			close(*prev_fd);
		if (token->cchar == PIPE && token->next)
		{
			close(pipe_fd[1]);
			*prev_fd = pipe_fd[0];
		}
	}
}

void	executor(t_ms **ms) //This is the function that will execute the commands from the parsing
{
	char	**env;
	t_token *token;
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
		if (!token->next && !token->fds && token->value && is_builtin(token->value[0]))
		{
			if (exec_builtin(token, *ms, true) < 0)
				return ((*ms)->last_status = 0, free_args(env));
		}
		exec_cmd(*ms, token, env, &prev_fd);
		token = next;
	}
	free_args(env);
}
