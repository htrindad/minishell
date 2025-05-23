/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:30 by mely-pan          #+#    #+#             */
/*   Updated: 2025/05/23 17:56:04 by htrindad         ###   ########.fr       */
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

bool	add_token(t_token **head, char **value, t_ms *ms, size_t *l) // This function needs a serious rework
{
	t_token	*new;
	size_t	i;

	i = *l;
	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (em("Error:\nMalloc failed\n", ms), true);
	if (!(*l) && mini_spec_case(ms->input, ms->scases))
	{
		new->value = NULL;
		new->cchar = set_case(ms->input);
		while (mini_spec_case(ms->input + i, ms->scases) \
				|| ms->input[i] == ' ')
			i++;
		*l = i;
		new->next = NULL;
		ft_lstadd_back((t_list **)head, (t_list *)new);
	}
	else
	{
		new->value = duplicator(value);
		if (!new->value)
			return (em("Error\nMalloc fail.\n", ms), true);
		while (ms->input[i])
		{
			if (spec_case(ms->input, ms->scases, l, i++, NULL))
			{
				new->cchar = set_case(ms->input + *l);
				break ;
			}
		}
		if (new->cchar != APPEND && new->cchar != HEREDOC)
			(*l)++;
		else
			(*l) += 2;
		new->next = NULL;
		ft_lstadd_back((t_list **)head, (t_list *)new);
	}
	return (false);
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
		if (args[i][0][0])
		{
			if (add_token(&head, args[i], shell, &l))
				return (free_tokens(head), NULL);
		}
		i++;
	}
	i = 0;
	while (args[i])
		free_args(args[i++]);
	if (DEBUG)
		print_tokens(head);
	return (head);
}
