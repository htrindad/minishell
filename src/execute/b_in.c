/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_in.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:53:56 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/06 20:54:20 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtin(t_token *token, t_ms *ms)
{
	return (single_exec(token, ms, true, NULL));
}

bool	is_single_token_and_builtin(t_token *token, int prev_fd)
{
	if (!token->next && !token->fds && token->value
			&& is_builtin(token->value[0]) && prev_fd == -1)
		return (true);
	return (false);
}
