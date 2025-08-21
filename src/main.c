/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:34 by mely-pan          #+#    #+#             */
/*   Updated: 2025/08/19 22:38:59 by htrindad         ###   ########.fr       */
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
	while (tok->next && is_redirection(tok->cchar))
		tok = tok->next;
	return (tok);
}

static inline bool	swap(t_token *token, t_token *last, size_t argc)
{
	size_t	i;

	i = 0;
	while (i < argc - 1)
	{
		token->value[i] = ft_strdup(last->value[i + 1]);
		if (token->value[i++] == NULL)
			return (true);
	}
	i = 1;
	while (last->value[i])
		free(last->value[i++]);
	last->value[1] = NULL;
	return (false);
}

static inline bool	change_set(t_token **token)
{
	t_token	*last;
	size_t	argc;

	if (!token || !*token)
		return (false);
	last = last_token(*token);
	argc = 0;
	if ((*token)->value == NULL && last && last->value
		&& is_redirection((*token)->cchar))
	{
		while (last->value[argc])
			argc++;
		(*token)->value = ft_calloc(argc + 1, sizeof(char *));
		if ((*token)->value == NULL)
			return (true);
		(*token)->value[argc] = NULL;
		if (swap(*token, last, argc))
			return (true);
	}
	if (DEBUG)
		print_tokens(*token);
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
	return (*es());
}
