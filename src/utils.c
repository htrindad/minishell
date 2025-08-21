/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:04:40 by htrindad          #+#    #+#             */
/*   Updated: 2025/08/21 17:36:57 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_slsh(int sig, siginfo_t *s, void *cont)
{
	(void)cont;
	(void)s;
	(void)sig;
	if (WTERMSIG(sig) == SIGQUIT)
		return (ft_putstr_fd("Quit (Core Dumped)\n", 1));
}

void	set_sigs(void)
{
	t_sa	sig;

	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sig.sa_sigaction = ctrl_slsh;
	sigaction(SIGQUIT, &sig, NULL);
}
