/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:21 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/20 20:31:43 by htrindad         ###   ########.fr       */
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
	builtin[2].name = NULL;
	builtin[3].name = "pwd";
	builtin[4].name = "export";
	builtin[5].name = "env";
	builtin[6].name = "unset";
	builtin[7].name = NULL;
	builtin[0].f = quit;
	builtin[1].f = change_dir;
	builtin[2].f = NULL;
	builtin[3].f = pwd;
	builtin[4].f = bi_export;
	builtin[5].f = env;
	builtin[6].f = unset;
	builtin[7].f = NULL;
	return (builtin);
}

//static void	display_banner(void)
//{
//	printf("\033[1;35m");
//	printf("  __  __ _       _     _          _ _ \n");
//	printf(" |  \\/  (_)_ __ (_)___| |__   ___| | |\n");
//	printf(" | |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |\n");
//	printf(" | |  | | | | | | \\__ \\ | | |  __/ | |\n");
//	printf(" |_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|\n");
//	printf("\n");
//	printf("     Created by htrindad & mely-pan\n");
//	printf("\033[0m");
//}

static inline char	*current_pwd(void)
{
	char	c[PATH_MAX];

	if (getcwd(c, sizeof(c)))
		return (ft_strdup(c));
	return (NULL);
}

void	init_ms(t_ms *shell)
{
	shell->shell_pid = getpid();
	shell->env = NULL;
	shell->input = NULL;
	shell->tokens = NULL;
	shell->scases = ft_split("< > | << >>", ' ');
	shell->running = true;
	shell->c_pwd = current_pwd();
	shell->builtin = init_bi();
	if (!shell->scases || !shell->builtin)
		em("Malloc\nFail.", shell);
	//display_banner();
}
