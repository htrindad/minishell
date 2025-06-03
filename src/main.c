/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:34 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/02 20:16:26 by htrindad         ###   ########.fr       */
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

static inline void	swap(t_token *curr, t_token *next)
{
	size_t	i;

	i = 0;
	next->value[0] = curr->value[0];
	next->value[1] = NULL;
	curr->value[0] = NULL;
	while (curr->value[i + 1])
	{
		curr->value[i] = curr->value[i + 1];
		i++;
	}
	curr->value[i] = NULL;
}

static inline bool	change_set(t_token **token)
{
	t_token	*curr;
	t_token	*next;

	if (!token || !*token)
		return (false);
	curr = *token;
	next = curr->next;
	if (curr->value == NULL && next && next->value)
	{
		curr->value = next->value;
		next->value = NULL;
		next->value = ft_calloc(2, sizeof(char *));
		if (next->value == NULL)
			return (true);
		swap(curr, next);
	}
	return (false);
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
		add_history(shell->input);
		shell->tokens = lexing(shell);
		if (change_set(&shell->tokens))
			break ;
		parse_redirections(&shell->tokens);
		executor(&shell);
		ret(shell);
	}
	clean_ms(shell);
	return (0);
}
