/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:57:01 by mely-pan          #+#    #+#             */
/*   Updated: 2025/04/11 14:46:56 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// iteration cases return the length of the next token.

size_t	iteration_cases(const char *s, size_t i)
{
	char	inside_q;
	size_t	l;

	inside_q = 0;
	l = 0;
	if (s[i] == '\'' || s[i] == '\"')
		l = iterate_through_q(s, i, &inside_q);
	else if (is_special_char(s[i]))
	{
		l = 1;
		if ((s[i] == '>' && s[i + 1] == '>') || (s[i] == '<' && s[i
					+ 1] == '<'))
			l++;
	}
	else
		while (s[i + l] && s[i + l] != ' ' && !is_special_char(s[i + l]))
			l += iterate_through_q(s, i, &inside_q);
	return (l);
}

size_t	iterate_through_q(const char *s, size_t i, char *quote_type)
{
	size_t	start;

	start = i;
	if (s[i] == '\'' || s[i] == '\"')
	{
		*quote_type = s[i++];
		while (s[i] && s[i] != *quote_type)
			i++;
		if (!s[i])
			return (perror("Error:\nUnclosed quotes"), 0);
		*quote_type = 0;
	}
	if (s[i])
		i++;
	return (i - start);
}
