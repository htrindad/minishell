/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:34 by mely-pan          #+#    #+#             */
/*   Updated: 2025/05/04 15:02:01 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_ms	*shell;

	(void)ac;
	(void)av;
	shell = ft_calloc(1, sizeof(t_ms));
	if (!shell)
		return (1);
	init_ms(shell);
	shell->env = get_env(env);
	while (shell->running)
	{
		shell->input = readline("minishell> ");
		if (!shell->input)
		{
			printf("exit\n");
			break ;
		}
		if (shell->input)
			add_history(shell->input);
		shell->tokens = lexing(shell);
		executor(shell);
		if (!ft_strncmp(shell->input, "exit", 4))
			break ;
		free(shell->input);
	}
	clean_ms(shell);
	return (0);
}
