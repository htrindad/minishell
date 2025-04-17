/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:14:57 by htrindad          #+#    #+#             */
/*   Updated: 2025/04/16 18:45:22 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ms	*g_ms;

static void	si(int pid)
{
	kill(pid, SIGINT);
	ft_putstr_fd(" ^C\n", 1);
}

//static void	sq(int pid)
//{
//	//TODO
//}

void	sig_handler(int sig, siginfo_t *s, void *content)
{
	(void)content;
	(void)s;
	if (sig == SIGINT)
		si(g_ms->pid);
	if (sig == SIGQUIT)
		kill(g_ms->pid, SIGQUIT);
}

void	refresh(t_ms *ms)
{
	g_ms = ms;
}
