/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:34 by mely-pan          #+#    #+#             */
/*   Updated: 2025/05/05 20:29:23 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_ms	*shell;
	t_sa	sa;

	(void)ac;
	(void)av;
	shell = ft_calloc(1, sizeof(t_ms));
	if (!shell)
		return (1);
	init_ms(shell);
	shell->env = get_env(env);
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = sig_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
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
		parse_redirections(&shell->tokens);
		executor(shell);
		free(shell->input);
	}
	clean_ms(shell);
	return (0);
}
