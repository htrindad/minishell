/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:10:16 by htrindad          #+#    #+#             */
/*   Updated: 2025/06/05 18:40:29 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*es(void)
{
	static int	status = 0;

	return (&status);
}

static int	rep(t_ms *ms, size_t i, bool is_parent)
{
	*es() = ms->builtin[i].f(ms);
	if (is_parent)
  {
    ms->last_satus = *es();
		return (*es());
  }
	else
	{
		ret(ms);
		clean_ms(ms);
		free_args(env);
		exit(*es());
	}
	return (*es());
}

int	single_exec(t_token *token, t_ms *ms, bool is_parent)
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
				return (rep(ms, i, is_parent));
			else if (!is_parent)
				return (rep(ms, i, is_parent));
		}
		i++;
	}
	return (1);
}

int	exec_builtin(t_token *token, t_ms *ms)
{
	return (single_exec(token, ms, true));
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

int	run_execve(char *cmd, char **full_cmd, char **env)
{
	if (cmd)
	{
		execve(cmd, full_cmd, env);
		perror("execve");
		if (errno == EACCES)
			return (126);
		return (1);
	}
	perror("Command not found");
	return (127);
}
