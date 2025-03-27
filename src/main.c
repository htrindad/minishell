/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:34 by mely-pan          #+#    #+#             */
/*   Updated: 2025/03/27 19:27:37 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_ms	shell;

	(void)argv;
	if (argc != 1)
		ft_putstr_fd("Run ./minishell with no args!", 2);
	init_ms(&shell);
	shell.env = get_env(env);
	while (1)
	{
		shell.input = readline("minishell> ");
		if (!shell.input)
		{
			printf("exit\n");
			break ;
		}
		if (shell.input)
			add_history(shell.input);
		lexing(&shell);
		if (ft_strncmp(shell.input, "exit", 4) == 0)
			break ;
		free(shell.input);
	}
	clean_ms(&shell);
	return (0);
}
