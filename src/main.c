/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:34 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/14 19:27:13 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	setup(t_ms *shell, char **env)
{
	init_ms(shell);
	shell->env = get_env(env);
	shell->home = ft_strdup(get_home(shell->env));
	if (shell->home == NULL)
	{
		shell->running = false;
		return ;
	}
	shell->si.sa_flags = SA_SIGINFO;
	sigemptyset(&shell->si.sa_mask);
	sigemptyset(&shell->sq.sa_mask);
	shell->si.sa_sigaction = sig_handler;
	shell->sq.sa_handler = SIG_IGN;
	sigaction(SIGINT, &shell->si, NULL);
	sigaction(SIGQUIT, &shell->sq, NULL);
}

static inline t_token	*last_token(t_token *tok)
{
	t_token	*last;

	last = tok;
	while (last->next)
		last = last->next;
	return (last);
}

static inline bool	swap(t_token *token, t_token *last)
{
	size_t	i;

	i = 0;
	last->cchar = NONE;
	last->next = NULL;
	last->value = ft_calloc(2, sizeof(char *));
	if (last->value == NULL)
		return (true);
	last->value[0] = token->value[0];
	while (token->value[i + 1])
	{
		token->value[i] = token->value[i + 1];
		i++;
	}
	token->value[i] = NULL;
	return (false);
}

static inline bool	change_set(t_token **token)
{
	t_token	*last;
	t_case	cc;
	t_token	*next;

	if (!token || !*token)
		return (false);
	last = last_token(*token);
	if ((*token)->value == NULL && last && last->value
		&& ((*token)->cchar == OUT || (*token)->cchar == APPEND))
	{
		cc = (*token)->cchar;
		next = (*token)->next;
		free(*token);
		*token = next;
		last->next = ft_calloc(1, sizeof(t_token));
		last->cchar = cc;
		if (last->next == NULL)
			return (true);
		if (swap(*token, last->next))
			return (true);
	}
	if (DEBUG)
		print_tokens_debug(*token);
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
		refresh(shell);
		shell->input = readline("minishell> ");
		if (shell->input == NULL)
			break ;
		add_history(shell->input);
		shell->tokens = lexing(shell);
		if (shell->tokens && change_set(&shell->tokens))
			break ;
		parse_redirections(&shell->tokens, shell->input);
		executor(&shell);
		ret(shell);
	}
	clean_ms(shell);
	return (0);
}
