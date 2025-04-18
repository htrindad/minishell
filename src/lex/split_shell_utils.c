/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:57:01 by mely-pan          #+#    #+#             */
/*   Updated: 2025/04/18 17:00:48 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	spec_case(char const *sub, char **cases, size_t *l, size_t y)
{
	int	i;
	size_t tmp;

	i = -1;
	if (l)
		*l = 0;
	while (++i < 5)
	{
		tmp = y;
		while (sub[tmp])
		{
			if (!ft_strncmp(sub, cases[i], ft_strlen(cases[i])))
			{
				if (l)
					*l = tmp;
				return (*l);
			}
			tmp++;
		}
	}
	return (0);
}

size_t	iteration_cases(const char *s, size_t i, char **cases, t_ms *ms)
{
	size_t	l;

	l = 0;
	if (spec_case(s, cases, &l, i))
		;
	else
		while (s[i + l] && s[i + l] != ' ' && !spec_case(s, \
					cases, (size_t *)0, l))
			l += iterate_through_q(s, i + l, ms);
	return (l);
}

size_t	iterate_through_q(const char *s, size_t i, t_ms *ms)
{
	size_t	start;
	char	quote_type;

	start = i;
	quote_type = 0;
	if (s[i] == '\'' || s[i] == '\"')
	{
		quote_type = s[i++];
		while (s[i] && s[i] != quote_type)
			i++;
		if (!s[i])
			return (em("Error:\nUnclosed quotes\n", ms), 0);
		quote_type = 0;
	}
	if (s[i])
		i++;
	return (i - start);
}
