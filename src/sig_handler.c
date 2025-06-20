/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:14:57 by htrindad          #+#    #+#             */
/*   Updated: 2025/06/05 19:00:09 by htrindad         ###   ########.fr       */
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

void	refresh(t_ms *ms)
{
	g_pid = ms->pid;
	ms->last_status = *es();
}

void	set_sig(struct sigaction *old_act)
{
	struct sigaction	new_act;

	sigaction(SIGINT, NULL, old_act);
	new_act.sa_handler = SIG_IGN;
	sigemptyset(&new_act.sa_mask);
	new_act.sa_flags = 0;
	sigaction(SIGINT, &new_act, NULL);
}
