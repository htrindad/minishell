/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:10:16 by htrindad          #+#    #+#             */
/*   Updated: 2025/06/03 17:54:26 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	rep(t_ms *ms, size_t i, bool is_parent, char **env)
{
	int	r;

	r = ms->builtin[i].f(ms);
	if (is_parent)
		return (0);
	else
	{
		ret(ms);
		clean_ms(ms);
		free_args(env);
		exit(r);
	}
	return (r);
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
				exit(rep(ms, i, is_parent, env));
		}
		i++;
	}
	return (-1);
}
