/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:21 by mely-pan          #+#    #+#             */
/*   Updated: 2025/04/30 20:19:40 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline t_builtin	*init_bi(void)
{
	t_builtin	*builtin;

	builtin = ft_calloc(8, sizeof(t_builtin));
	builtin[0] = (t_builtin){.name="exit", .f=quit},
	builtin[1] = (t_builtin){.name="cd", .f=change_dir},
	builtin[2] = (t_builtin){.name="echo", .f=echo},
	builtin[3] = (t_builtin){.name="pwd", .f=pwd},
	builtin[4] = (t_builtin){.name="export", .f=bi_export},
	builtin[5] = (t_builtin){.name="env", .f=env},
	builtin[6] = (t_builtin){.name="unset", .f=unset},
	builtin[7] = (t_builtin){.name=NULL, .f=NULL};
	return (builtin);
}

void	init_ms(t_ms *shell)
{
	shell->env = NULL;
	shell->input = NULL;
	shell->last_status = 0;
	shell->tokens = NULL;
	shell->scases = ft_split("< > | << >>", ' ');
	shell->running = true;
	shell->builtin = init_bi();
	if (!shell->scases || !shell->builtin)
		em("Malloc\nFail.\n", shell);
}
