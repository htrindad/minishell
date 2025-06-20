/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:10:16 by htrindad          #+#    #+#             */
/*   Updated: 2025/06/20 19:41:07 by htrindad         ###   ########.fr       */
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
	if (is_parent)
		return (*es());
	else
	{
		ret(ms);
		clean_ms(ms);
		free_args(env);
		exit(*es());
	}
	return (*es());
}

int	single_exec(t_token *token, t_ms *ms, bool is_parent, char **env)
{
	size_t	i;

	i = 0;
	while (ms->builtin[i].name)
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
		i++;
	}
	return (1);
}

bool	swap_strs(char **s1, char *s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = ft_strdup(s2);
	if (s1 == NULL)
		return (true);
	free(tmp);
	return (false);
}

int	run_execve(char *cmd, char **full_cmd, char **env, char *value)
{
	if (cmd)
	{
		execve(cmd, full_cmd, env);
		perror("execve");
		if (!access(cmd, F_OK))
			return (126);
		if (access(cmd, X_OK))
			return (127);
		return (1);
	}
	ft_putstr_fd(value, 2);
	perror(" Command not found");
	return (127);
}
