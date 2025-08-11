/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:14:57 by htrindad          #+#    #+#             */
/*   Updated: 2025/08/11 17:31:05 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_pid;

static void	si(void)
{
	if (g_pid > 0)
		kill(g_pid, SIGINT);
	*es() = 130;
}

void	sig_handler(int sig, siginfo_t *s, void *content)
{
	(void)content;
	(void)s;
	if (*in_heredoc())
		return ;
	if (sig == SIGINT)
		si();
	ft_putchar_fd('\n', 1);
	if (!g_pid)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	h_setter(int sig, siginfo_t *s, void *content)
{
	(void)sig;
	(void)s;
	(void)content;
	*es() = 130;
	ret(*b_ms());
	clean_ms(*b_ms());
	exit(130);
}

void	hsh(t_ms *ms)
{
	t_sa	sa;

	signal(SIGQUIT, SIG_IGN);
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = h_setter;
	sigaction(SIGINT, &sa, NULL);
	*b_ms() = ms;
}

void	refresh(t_ms *ms)
{
	g_pid = ms->pid;
}
