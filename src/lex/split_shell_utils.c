/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:57:01 by mely-pan          #+#    #+#             */
/*   Updated: 2025/04/21 17:51:05 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	spec_case(char const *sub, char **cases, size_t *l, size_t y, bool *cas)
{
	int		i;
	size_t	cases_len;

	if (cas)
		*cas = true;
	if (l)
		*l = 0;
	while (sub[y])
	{
		i = -1;
		while (++i < 5)
		{
			cases_len = ft_strlen(cases[i]);
			if (ft_strlen(sub + y) >= cases_len && !ft_strncmp(sub + y, cases[i], cases_len))
			{
				if (l)
					*l = y;
				if (cas)
					*cas = false;
				return (y);
			}
		}
		y++;
	}
	return (0);
}

size_t	iteration_cases(const char *s, size_t i, char **cases, t_ms *ms)
{
	size_t	l;

	l = 0;
	if (spec_case(s, cases, &l, i, NULL))
		;
	else
		while (s[i + l] && s[i + l] != ' ' && !spec_case(s, \
					cases, (size_t *)0, l, NULL))
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
