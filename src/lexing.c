/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:30 by mely-pan          #+#    #+#             */
/*   Updated: 2025/05/31 20:21:42 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static inline void	print_type(t_case ccase)
{
	if (ccase == NONE)
		printf("NONE ");
	if (ccase == OUT)
		printf("OUT ");
	if (ccase == IN)
		printf("IN ");
	if (ccase == PIPE)
		printf("PIPE ");
	if (ccase == HEREDOC)
		printf("HEREDOC ");
	if (ccase == APPEND)
		printf("APPEND");
}

void	print_tokens(t_token *head)
{
	t_token	*tmp;
	size_t	i;

	tmp = head;
	while (tmp)
	{
		i = 0;
		printf("(");
		while (tmp->value && tmp->value[i])
			printf("[%s]", tmp->value[i++]);
		printf(") ");
		print_type(tmp->cchar);
		tmp = tmp->next;
	}
	printf("\n");
}

static void	fa_spec(char ***args)
{
	size_t	i;

	i = 1;
	while (args[i])
		free_args(args[i++]);
	free(args);
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
	if (args[0] == NULL && args[1] != NULL)
		if (add_token(&head, args[i++], shell, &l))
			return (free_tokens(head), NULL);
	while (args[i])
	{
		if (args[i][0][0])
		{
			if (add_token(&head, args[i], shell, &l))
				return (free_tokens(head), NULL);
		}
		i++;
	}
	if (args[0])
	{
		i = 0;
		while (args[i])
			free_args(args[i++]);
		free(args);
	}
	else
		fa_spec(args);
	return (head);
}
