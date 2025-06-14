/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:33:47 by mely-pan          #+#    #+#             */
/*   Updated: 2025/05/31 20:20:10 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_token(t_token **head, t_token *to_remove)
{
	t_token	*prev;
	t_token	*curr;

	prev = NULL;
	curr = *head;
	while (curr)
	{
		if (curr == to_remove)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			free_args(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static void	shift_args_left(char **args)
{
	int	i;

	i = 0;
	free(args[0]);
	while (args[i + 1])
	{
		args[i] = args[i + 1];
		i++;
	}
	args[i] = NULL;
}

static void	remove_redir(t_token *redir)
{
	t_token	*file;

	file = redir->next;
	if (file && file->value && file->value[0] && file->value[1])
		shift_args_left(file->value);
	else
	{
		if (DEBUG && file && file->value)
			printf("Removing %s\n", file->value[0]);
		if (file)
		{
			redir->next = file->next;
			if (is_redirection(file->cchar))
				redir->cchar = file->cchar;
			else
				redir->cchar = NONE;
			free_args(file->value);
			free(file);
		}
		else
			redir->cchar = NONE;
	}
}

void	cleanup_redir(t_token **tokens)
{
	t_token	*curr;
	t_token	*prev;

	curr = *tokens;
	prev = NULL;
	while (curr)
	{
		if (is_redirection(curr->cchar))
		{
			remove_redir(curr);
			if (prev)
				curr = prev;
			else
				curr = *tokens;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}
void	set_sig(struct sigaction *old_act)
{
	struct sigaction	new_act;

	sigaction(SIGINT, NULL, &old_act);
	new_act.sa_handler = SIG_IGN;
	sigemptyset(&new_act.sa_mask);
	new_act.sa_flags = 0;
	sigaction(SIGINT, &new_act, NULL);
}
