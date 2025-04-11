/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:34 by mely-pan          #+#    #+#             */
/*   Updated: 2025/04/11 16:10:40 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_ms	shell;

	(void)argv;
	(void)argc;
	init_ms(&shell);
	shell.env = get_env(env);
	while (shell->running)
	{
		shell.input = readline("minishell> ");
		if (!shell.input)
		{
			printf("exit\n");
			break ;
		}
		if (shell.input)
			add_history(shell.input);
		shell.tokens = lexing(&shell);
		if (ft_strncmp(shell.input, "exit", 4) == 0)
			break ;
		free(shell.input);
	}
	clean_ms(&shell);
	return (0);
}
