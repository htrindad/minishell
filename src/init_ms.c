/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:21 by mely-pan          #+#    #+#             */
/*   Updated: 2025/05/14 18:40:59 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline t_builtin	*init_bi(void)
{
	t_builtin	*builtin;

	builtin = ft_calloc(8, sizeof(t_builtin));
	if (builtin == NULL)
		return (NULL);
	builtin[0].name = "exit";
	builtin[1].name = "cd";
	builtin[2].name = "echo";
	builtin[3].name = "pwd";
	builtin[4].name = "export";
	builtin[5].name = "env";
	builtin[6].name = "unset";
	builtin[7].name = NULL;
	builtin[0].f = quit;
	builtin[1].f = change_dir;
	builtin[2].f = echo;
	builtin[3].f = pwd;
	builtin[4].f = bi_export;
	builtin[5].f = env;
	builtin[6].f = unset;
	builtin[7].f = NULL;
	return (builtin);
}

void	init_ms(t_ms *shell)
{
	shell->shell_pid = getpid();
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
