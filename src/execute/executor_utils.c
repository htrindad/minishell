/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:26:00 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/02 20:45:26 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_builtin(char *cmd)
{
	size_t	len;

	len = ft_strlen(cmd);
	return (!ft_strncmp(cmd, "echo", len) || !ft_strncmp(cmd, "cd", len)
		|| !ft_strncmp(cmd, "pwd", len) || !ft_strncmp(cmd, "export", len) \
		|| !ft_strncmp(cmd, "unset", len) || !ft_strncmp(cmd, "env", len) \
		|| !ft_strncmp(cmd, "exit", len));
}

static int	is_path(char *cmd)
{
	return (cmd && (cmd[0] == '/' || !ft_strncmp(cmd, "./", 2)
			|| !ft_strncmp(cmd, "../", 3)));
}

static char	*try_paths(char *cmd, char **paths)
{
	int		i;
	char	*full_path;
	int		len;

	i = 0;
	while (paths[i])
	{
		len = ft_strlen(paths[i]);
		full_path = ft_calloc(len + ft_strlen(cmd) + 2, 1);
		if (!full_path)
			return (NULL);
		ft_strlcpy(full_path, paths[i], len + 1);
		ft_strlcat(full_path, "/", len + 2);
		ft_strlcat(full_path, cmd, len + ft_strlen(cmd) + 2);
		if (!access(full_path, X_OK))
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command(char *cmd, char **env, t_ms *ms)
{
	char	**paths;
	char	*result;

	if (is_path(cmd))
	{
		result = ft_strdup(cmd);
		if (!result)
			return (NULL);
		return (result);
	}
	paths = get_paths(env, ms);
	if (!paths)
		return (NULL);
	result = try_paths(cmd, paths);
	free_args(paths);
	return (result);
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
			if (!paths)
				return (em("Error\nMalloc Fail.\n", ms), NULL);
			return (paths);
		}
		i++;
	}
	return (NULL);
}
