/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:28:47 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/02 19:50:26 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	print_value(char **value)
{
	int	i;

	i = 0;
	if (!value)
	{
		printf("Value     : (null)\n");
		return ;
	}
	printf("Value     : ");
	while (value[i])
	{
		printf("\"%s\" ", value[i]);
		i++;
	}
	printf("\n");
}

void	print_redirs(t_redir *redir, const char *label)
{
	while (redir)
	{
		printf("  [%s] %s (type: %d)\n", label, redir->filename, redir->type);
		redir = redir->next;
	}
}

void	print_fds(t_fds *fds)
{
	if (!fds)
	{
		printf("  [FDS] No redirections\n");
		return ;
	}
	if (!fds->in && !fds->out)
	{
		printf("  [FDS] No input or output redirections\n");
		return ;
	}
	if (fds->in)
		print_redirs(fds->in, "IN");
	if (fds->out)
		print_redirs(fds->out, "OUT");
}

void	print_tokens_debug(t_token *head)
{
	int	i;

	i = 0;
	while (head)
	{
		printf("\n=== Token #%d ===\n", i++);
		print_value(head->value);
		printf("cchar     : %d\n", head->cchar);
		print_fds(head->fds);
		printf("==========\n");
		head = head->next;
	}
}
