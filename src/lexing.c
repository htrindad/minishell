/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:30 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/02 19:46:20 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	lex_free(args);
	return (head);
}
