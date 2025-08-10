/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:03:30 by htrindad          #+#    #+#             */
/*   Updated: 2025/08/10 17:11:37 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl_checker(char *es, t_env *new)
{
	int	lvl;

	if (!ft_strncmp(new->key, "SHLVL", 6))
	{
		lvl = ft_atoi(es + 1) + 1;
		new->value = ft_itoa(lvl);
	}
	else
		new->value = ft_strdup(es + 1);
}

bool	change_the_score(t_env *env, t_token *tok)
{
	size_t	i;

	i = 0;
	while (tok->value[i + 1])
		i++;
	if (change_ms(env, "_", tok->value[i]))
		return (false);
	return (true);
}
