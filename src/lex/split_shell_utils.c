/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:57:01 by mely-pan          #+#    #+#             */
/*   Updated: 2025/04/11 16:15:43 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// spec_case will compare the sub with one of the cases "< > | << >>"
bool	spec_case(char *sub, char **cases, size_t *l)
{
	int	i;

	i = -1;
	l = NULL;
	while (++i < 5)
	{
		if (!ft_strcmp(sub, cases[i], ft_strlen(cases[i])))
		{
			*l = ft_strlen(cases[i]);
			return (true);
		}
	}
	return (false);
}

// iteration cases return the length of the next token.
size_t	iteration_cases(const char *s, size_t i, char **cases, t_ms *ms)
{
	char	*tmp;
	size_t	l;

	l = 0;
	tmp = ft_substr(s, i, 2);
	if (tmp == NULL)
		return (0);
	if (s[i] == '\'' || s[i] == '\"')
		l = iterate_through_q(s, i);
	else if (spec_case(tmp, cases, &l))
		;
	else
		while (s[i + l] && s[i + l] != ' ' && spec_case(tmp, \
					cases, (size_t *)0))
			l += iterate_through_q(s, i);
	return (free(tmp), l);
}

// Unecessary variable "quote_type" always becomes '\0'. I will also remove the "inside_q" var from "iteration_cases"
size_t	iterate_through_q(const char *s, size_t i, t_ms *ms)
{
	size_t	start;
	char	quote_type

	start = i;
	quote_type = 0;
	if (s[i] == '\'' || s[i] == '\"')
	{
		quote_type = s[i++];
		while (s[i] && s[i] != quote_type)
			i++;
		if (!s[i])
			return (em("Error:\nUnclosed quotes", ms), 0);
		quote_type = 0;
	}
	if (s[i])
		i++;
	return (i - start);
}
