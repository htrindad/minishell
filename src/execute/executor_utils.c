/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:26:00 by mely-pan          #+#    #+#             */
/*   Updated: 2025/04/30 20:27:21 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_builtin(char *cmd)
{
	return (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5));
}

int	exec_builtin(t_token *token, t_ms *ms, bool is_parent)
{
	int	i;

	i = 0;
	while (ms->builtin[i].name)
	{
		if (token->value[0] && ms->builtin[i].name
			&& !ft_strncmp(token->value[0], ms->builtin[i].name,
				ft_strlen(ms->builtin[i].name) + 1))
		{
			if (is_parent && token->value && (!ft_strncmp(token->value[0], "cd",
						3) || !ft_strncmp(token->value[0], "export", 7)
					|| !ft_strncmp(token->value[0], "unset", 6)
					|| !ft_strncmp(token->value[0], "exit", 5)))
				return (ms->builtin[i].f(ms));
			else if (!is_parent)
				exit(ms->builtin[i].f(ms));
		}
		i++;
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
		full_path = ft_calloc(path_len + ft_strlen(cmd_args + 2), 1);
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
