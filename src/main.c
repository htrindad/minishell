/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:34 by mely-pan          #+#    #+#             */
/*   Updated: 2025/05/14 19:37:26 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline t_sa	setup(t_ms *shell, char **env)
{
	t_sa	sa;

	init_ms(shell);
	shell->env = get_env(env);
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = sig_handler;
	sigaction(SIGINT, &sa, NULL);
	return (sa);
}

int	main(int ac, char **av, char **env)
{
	t_ms	*shell;
	t_sa	sa;

	(void)ac;
	(void)av;
	shell = ft_calloc(1, sizeof(t_ms));
	if (shell == NULL)
		return (1);
	sa = setup(shell, env);
	while (shell->running)
	{
		shell->pid = 0;
		refresh(shell->pid);
		shell->input = readline("minishell> ");
		if (shell->input == NULL)
			break ;
		else
			add_history(shell->input);
		shell->tokens = lexing(shell);
		parse_redirections(&shell->tokens);
		executor(shell);
		free(shell->input);
	}
	clean_ms(shell);
	return (0);
}
