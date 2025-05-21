/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:10:16 by htrindad          #+#    #+#             */
/*   Updated: 2025/05/21 19:35:48 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			if(is_parent && token->value && is_builtin(token->value[0]))
				return (ms->builtin[i].f(ms), 0);
			else if (!is_parent)
				exit(ms->builtin[i].f(ms));
		}
		i++;
	}
	return (-1);
}

int	redir_exec(t_token *token, t_ms *ms)
{
	char	**env;

	env = comp_env(ms->env);
	if (env == NULL)
		return (em("Error\nMalloc Fail.", ms), -1);
	if (token->fds)
		if (handle_redirections(&token))
			return (em("Failed.", ms), -1);
	single_exec(token, ms, false);
	exit(0); //wtf?
	return (0);
}
