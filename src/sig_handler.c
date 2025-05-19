/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:14:57 by htrindad          #+#    #+#             */
/*   Updated: 2025/05/16 19:11:40 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_pid;

static void	si(void)
{
	if (g_pid > 0)
		kill(g_pid, SIGINT);
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

void	refresh(int pid)
{
	g_pid = pid;
}
