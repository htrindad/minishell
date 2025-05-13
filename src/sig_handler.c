/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:14:57 by htrindad          #+#    #+#             */
/*   Updated: 2025/05/13 20:22:35 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ms	*g_ms;

static void	si(int pid)
{
	if (!g_ms)
		return ;
	if (pid > 0)
		kill(pid, SIGINT);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sq(int pid)
{
	if (g_ms && pid > 0)
	{
		kill(pid, SIGQUIT);
		ft_putstr_fd("\nQuit: 3\n", 2);
	}
}

void	sig_handler(int sig, siginfo_t *s, void *content)
{
	(void)content;
	(void)s;
	if (sig == SIGINT)
			si(g_ms->pid);
	if (sig == SIGQUIT)
			sq(g_ms->pid);
}

void	refresh(t_ms *ms)
{
	g_ms = ms;
}
