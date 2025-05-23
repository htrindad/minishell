/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:34 by mely-pan          #+#    #+#             */
/*   Updated: 2025/05/16 18:27:44 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	setup(t_ms *shell, char **env)
{
	init_ms(shell);
	shell->env = get_env(env);
	shell->si.sa_flags = SA_SIGINFO;
	sigemptyset(&shell->si.sa_mask);
	sigemptyset(&shell->sq.sa_mask);
	shell->si.sa_sigaction = sig_handler;
	shell->sq.sa_handler = SIG_IGN;
	sigaction(SIGINT, &shell->si, NULL);
	sigaction(SIGQUIT, &shell->sq, NULL);
}

int	main(int ac, char **av, char **env)
{
	t_ms	*shell;

	(void)ac;
	(void)av;
	shell = ft_calloc(1, sizeof(t_ms));
	if (shell == NULL)
		return (1);
	setup(shell, env);
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
		executor(&shell);
		free(shell->input);
	}
	clean_ms(shell);
	return (0);
}
