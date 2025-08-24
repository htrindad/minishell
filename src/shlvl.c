/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:03:30 by htrindad          #+#    #+#             */
/*   Updated: 2025/08/22 17:30:40 by htrindad         ###   ########.fr       */
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

void	close_hds(t_token *token)
{
	t_redir	*tmp;

	while (token && token->fds && token->fds->in)
	{
		tmp = token->fds->in;
		while (tmp)
		{
			if (tmp->heredoc_fd > 2)
				close(tmp->heredoc_fd);
			tmp = tmp->next;
		}
		token = token->next;
	}
}

long	ft_atol(char *nptr)
{
	long	num;
	long	neg;
	size_t	i;

	num = 0;
	neg = 1;
	i = 0;
	while (nptr[i] == 32 || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			neg = -1;
	while (ft_isdigit((int)nptr[i]))
	{
		num = num * 10 + (nptr[i] - 48);
		i++;
	}
	return (num * neg);
}

void	pump_n_dump(size_t *i, int *q)
{
	(*i)++;
	*q = 1;
}

void	problem(t_env *env, char *str, t_ms *ms)
{
	if (add_env(&env, str))
		em("Error: Malloc Fail.", ms, 0);
	free(str);
}
