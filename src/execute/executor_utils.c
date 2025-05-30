/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:26:00 by mely-pan          #+#    #+#             */
/*   Updated: 2025/05/30 20:56:25 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_builtin(char *cmd)
{
	return (!ft_strncmp(cmd, "echo", 4) || !ft_strncmp(cmd, "cd", 2)
		|| !ft_strncmp(cmd, "pwd", 3) || !ft_strncmp(cmd, "export", 6) \
		|| !ft_strncmp(cmd, "unset", 5) || !ft_strncmp(cmd, "env", 3) \
		|| !ft_strncmp(cmd, "exit", 4));
}

int	exec_builtin(t_token *token, t_ms *ms, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	if (token->cchar == PIPE && token->next)
		if (pipe(pipe_fd) < 0)
			return (em("Pipe Fail.", ms), -1);
	if (!ft_strncmp(token->value[0], "exit", 5) \
			|| !ft_strncmp(token->value[0], "export", 6) \
			|| !ft_strncmp(token->value[0], "unset", 5))
	{
		(void)pid;
		single_exec(token, ms, true);
	}
	else
	{
		pid = fork();
		if (pid < 0)
			return (em("Error\nFork fail.\n", ms), -1);
		if (!pid)
			exec_child(token, env, -1, pipe_fd, ms);
		if (pid)
		{
			ms->pid = pid;
			refresh(ms->pid);
			if (waitpid(ms->pid, &status, 0) == -1)
				ms->last_status = 1;
			else if (WIFEXITED(status))
				ms->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				ms->last_status = WTERMSIG(status) + 128;
			else
				ms->last_status = 1;
		}
	}
	return (0); // not a b-in
}

char	*find_command(char *cmd_args, char **env, t_ms *ms)
{
	char	**paths;
	char	*full_path;
	int		i;
	int		path_len;

	paths = get_paths(env, ms);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path_len = ft_strlen(paths[i]);
		full_path = ft_calloc(path_len + ft_strlen(cmd_args) + 2, 1);
		if (!full_path)
			return (free_args(paths), NULL);
		ft_strlcpy(full_path, paths[i], path_len + 1);
		ft_strlcat(full_path, "/", path_len + 2);
		ft_strlcat(full_path, cmd_args, path_len + ft_strlen(cmd_args) + 2);
		if (!access(full_path, X_OK))
			return (free_args(paths), full_path);
		free(full_path);
		i++;
	}
	free_args(paths);
	return (NULL);
}

char	**get_paths(char **env, t_ms *ms)
{
	int		i;
	char	*path_var;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			path_var = env[i] + 5;
			paths = ft_split(path_var, ':');
			if (paths == NULL)
				return (em("Error\nMalloc Fail.\n", ms), NULL);
			return (paths);
		}
		i++;
	}
	return (NULL);
}
