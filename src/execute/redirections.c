/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:33:47 by mely-pan          #+#    #+#             */
/*   Updated: 2025/05/19 20:33:59 by htrindad         ###   ########.fr       */
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

static void	remove_redir(t_token **tokens, t_token *prev, t_token *redir)
{
	t_token *file;

	file = redir->next;
	if (file && file->value && file->value[1])
		shift_args_left(file->value);
	else
	{
		if (DEBUG)
			printf("Removing %s\n", file->value[0]);
		if (file)
		{
			redir->next = file->next;
			free_args(file->value);
			free(file);
		}
	}
	if (prev)
		prev->next = redir->next;
	else
		*tokens = redir->next;
}

void	cleanup_redir(t_token **tokens)
{
	t_token *curr;
	t_token *prev;

	curr = *tokens;
	prev = NULL;
	while (curr)
	{
		if (is_redirection(curr->cchar))
		{
			remove_redir(tokens, prev, curr);
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

