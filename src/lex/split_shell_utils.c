/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:57:01 by mely-pan          #+#    #+#             */
/*   Updated: 2025/04/16 17:39:30 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	spec_case(char const *sub, char const **cases, size_t *l, size_t y)
{
	int	i;

	i = -1;
	*l = 0;
	while (++i < 5)
	{
		while (sub[y])
		{
			if (!ft_strncmp(sub, cases[i], ft_strlen(cases[i])))
			{
				*l = y;
				return (*l);
			}
			y++;
		}
	}
	return (0);
}

size_t	iteration_cases(const char *s, size_t i, char **cases, t_ms *ms)
{
	char	*tmp;
	size_t	l;

	l = 0;
	tmp = ft_substr(s, i, 2);
	if (tmp == NULL)
		return (em("Error\nMalloc fail.\n", ms), 0);
	if (s[i] == '\'' || s[i] == '\"')
		l = iterate_through_q(s, i, ms);
	else if (spec_case(tmp, cases, &l, i))
		;
	else
		while (s[i + l] && s[i + l] != ' ' && spec_case(tmp, \
					cases, (size_t *)0))
			l += iterate_through_q(s, i, ms);
	return (free(tmp), l);
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
