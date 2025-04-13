/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:30 by mely-pan          #+#    #+#             */
/*   Updated: 2025/04/13 17:26:51 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The Purpose of lexing is to separate the user input into tokens the
// same way the shell does, for that we must have in consideration quotes,
// special characteres (>, <, |, >>, <<), spaces and $env_var.
// The tokens will be stored in a linked list of t_token structs.
// ex: echo "$HOME path" -> [echo] [./user/home path]

bool	add_token(t_token **head, char *value, t_ms *ms) // This function needs a serious rework
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (em("Error:\nMalloc failed\n", ms), true);
	new->value = ft_strdup(value);
	if (!new->value)
		return (free(new), 0);
	new->next = NULL;
	ft_lstadd_back((t_list **)head, (t_list *)new);
	return (false);
}

static void	print_tokens(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("[%s]\n", tmp->value);
		tmp = tmp->next;
	}
}

t_token	*lexing(t_ms *shell)
{
	t_token	*head;
	char	**args;
	int		i;

	head = NULL;
	args = ft_split_shell(shell);
	if (!args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		if (add_token(&head, args[i++], shell))
		{
			free_tokens(head);
			return (NULL);
		}
	}
	if (DEBUG)
		print_tokens(head);
	free_args(args);
	return (head);
}
