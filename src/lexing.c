/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:30 by mely-pan          #+#    #+#             */
/*   Updated: 2025/08/23 19:33:22 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	all_spaces(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		if (s[i++] != ' ')
			return (false);
	return (true);
}

bool	f_spec_case(char const *s, size_t *i, char **cases)
{
	bool	sc;
	bool	os;

	sc = false;
	os = true;
	if (s[*i] != ' ')
		os = false;
	while (s[*i] == ' ' || mini_spec_case(s + *i, cases))
	{
		if (s[*i] != ' ')
			os = false;
		if (mini_spec_case(s + *i, cases))
			sc = true;
		(*i)++;
	}
	if (os && *i)
		(*i)--;
	return (sc);
}

t_case	set_case(char const *c)
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

static void	null_fds(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->fds)
			tmp->fds = NULL;
		tmp = tmp->next;
	}
}

t_token	*lexing(t_ms *shell)
{
	t_token	*head;
	t_info	args;
	size_t	i;

	head = NULL;
	args = ft_split_shell(shell);
	if (args.ptr == NULL)
		return (NULL);
	i = 0;
	*counter() = 0;
	while (i < args.count)
		if (add_token(&head, args.ptr[i++], shell))
			return (lex_free(args), free_tokens(head), NULL);
	if (check_parse_error(shell))
		return (null_fds(head), lex_free(args), free_tokens(head), NULL);
	if (DEBUG)
		print_tokens(head);
	return (null_fds(head), lex_free(args), head);
}
