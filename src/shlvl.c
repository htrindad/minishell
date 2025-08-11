/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:03:30 by htrindad          #+#    #+#             */
/*   Updated: 2025/08/11 18:47:44 by mely-pan         ###   ########.fr       */
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

	while (token)
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
