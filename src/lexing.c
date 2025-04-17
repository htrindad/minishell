/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:30 by mely-pan          #+#    #+#             */
/*   Updated: 2025/04/17 18:32:04 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The Purpose of lexing is to separate the user input into tokens the
// same way the shell does, for that we must have in consideration quotes,
// special characteres (>, <, |, >>, <<), spaces and $env_var.
// The tokens will be stored in a linked list of t_token structs.
// ex: echo "$HOME path" -> [echo] [./user/home path]

static t_case	set_case(char const *c)
{
	if (c[0] == '|')
		return (PIPE);
	if (c[0] == '>')
	{
		if (c[1] == '>')
			return (APPEND);
		else
			return (OUT);
	}
	if (c[0] == '<')
	{
		if (c[1] == '<')
			return (HEREDOC);
		else
			return (IN);
	}
	return (NONE);
}

bool	add_token(t_token **head, char **value, t_ms *ms, size_t *l) // This function needs a serious rework
{
	t_token	*new;
	size_t	i;

	i = *l;
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (em("Error:\nMalloc failed\n", ms), true);
	new->value = duplicator(value);
	printf("1st\n");
	if (!new->value)
		return (em("Error\nMalloc fail.\n", ms), true);
	while (ms->input[i])
	{
		if (spec_case(ms->input, ms->scases, l, i++))
		{
			new->cchar = set_case(ms->input + *l);
			break ;
		}
	}
	*l = i;
	new->next = NULL;
	ft_lstadd_back((t_list **)head, (t_list *)new);
	return (false);
}

static void	print_tokens(t_token *head)
{
	t_token	*tmp;
	size_t	i;

	tmp = head;
	while (tmp)
	{
		i = 0;
		ft_putchar_fd('(', 1);
		while (tmp->value[i])
			printf("[%s]", tmp->value[i++]);
		ft_putchar_fd(')', 1);
		tmp = tmp->next;
	}
}

t_token	*lexing(t_ms *shell)
{
	t_token	*head;
	char	***args;
	size_t	l;
	int		i;

	head = NULL;
	args = ft_split_shell(shell);
	if (!args)
		return (NULL);
	i = 0;
	l = 0;
	while (args[i])
	{
		printf("Entrei\n");
		if (add_token(&head, args[i++], shell, &l))
			return (free_tokens(head), NULL);
	}
	i = 0;
	while (args[i])
		free_args(args[i++]);
	if (DEBUG)
		print_tokens(head);
	return (head);
}
