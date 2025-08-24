/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:10:16 by htrindad          #+#    #+#             */
/*   Updated: 2025/08/24 13:42:16 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*es(void)
{
	static int	status = 0;

	return (&status);
}

static int	rep(t_ms *ms, size_t i, bool is_parent, char **env)
{
	*es() = ms->builtin[i].f(ms);
	return (case_free(is_parent, env, ms));
}

int	single_exec(t_token *token, t_ms *ms, bool is_parent, char **env)
{
	size_t	i;

	i = 0;
	while (i < 8)
	{
		if (token->value[0] && ms->builtin[i].name
			&& !ft_strncmp(token->value[0], ms->builtin[i].name,
				ft_strlen(ms->builtin[i].name) + 1))
		{
			if (is_parent && token->value && is_builtin(token->value[0]))
				return (rep(ms, i, is_parent, env));
			else if (!is_parent)
				return (rep(ms, i, is_parent, env));
		}
		if (i == 2 && token->value[0]
			&& !ft_strncmp("echo", token->value[0],
				ft_strlen(token->value[0])))
		{
			*es() = echo(token->value + 1);
			return (case_free(is_parent, env, ms));
		}
		i++;
	}
	return (case_free(is_parent, env, ms), 1);
}

bool	swap_strs(char **s1, char *s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = ft_strdup(s2);
	if (s1 == NULL)
	{
		ft_putstr_fd("Malloc error.\n", 2);
		if (s2)
			free(s2);
		return (true);
	}
	free(tmp);
	return (false);
}

int	run_execve(char *cmd, char **full_cmd, char **env, char *value)
{
	if (cmd)
	{
		if (!ft_strncmp(full_cmd[0], ".", ft_strlen(full_cmd[0]))
			&& !full_cmd[1])
			return (2);
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
		execve(cmd, full_cmd, env);
		perror("execve");
		if (!access(cmd, F_OK))
			return (free(cmd), 126);
		if (access(cmd, X_OK))
			return (free(cmd), 127);
		return (1);
	}
	ft_putstr_fd(value, 2);
	ft_putstr_fd(": Command not found\n", 2);
	return (127);
}
