/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:21 by mely-pan          #+#    #+#             */
/*   Updated: 2025/04/11 15:11:02 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline t_builtin	*init_bi(void)
{
	t_builtin	*builtin;

	builtin =
	{
		{.name="exit", .f=quit};
		{.name="cd", .f=NULL};
		{.name="echo", .f=NULL};
		{.name="pwd", .f=NULL};
		{.name="export", .f=NULL};
		{.name="env", .f=NULL};
		{.name="unset", .f=NULL};
	};
	return (builtin);
}

void	init_ms(t_ms *shell)
{
	shell = ft_calloc(1, sizeof(t_ms));
	shell->env = NULL;
	shell->input = NULL;
	shell->last_status = 0;
	shell->tokens = NULL;
	shell->scases = ft_split("< > | << >>", ' ');
}
