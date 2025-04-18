/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:00:00 by htrindad          #+#    #+#             */ /*   Updated: 2025/04/17 18:40:56 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	count_cases(char const *s, t_ms *ms)
{
	size_t	i;
	size_t	count;
	size_t	tmp;
	size_t	l;

	i = 0;
	l = 0;
	count = 0;
	tmp = 0;
	while (s[i])
	{
		while (!tmp && s[i])
			tmp += spec_case(s, ms->scases, &l, i++);
		count++;
		if (!s[i])
			break;
		while (s[i])
		{
			tmp += spec_case(s, ms->scases, &l, i);
			count += tmp;
			i += tmp;
		}
	}
	return (count);
}

static inline bool	check(char const *s, char **cases, size_t i, t_ms *ms)
{
	char	*tmp;
	bool	cas;
	
	tmp = ft_substr(s, i, 2);
	cas = true;
	if (tmp == NULL)
		return (em("Error\nMalloc Fail.\n", ms), 0);
	if (spec_case(tmp, cases, NULL, i))
		cas = false;
	return (free(tmp), cas);
}

size_t	ft_count_words(char const *s, t_ms *ms, size_t max) // The objective of this function is to get the words under a length.
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] && i < max)
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		count++;
		if (s[i] == '\'' || s[i] == '\"')
			i += iterate_through_q(s, i, ms);
		else
			while (s[i] && s[i] != ' ' && check(s, ms->scases, i, ms))
				i += iterate_through_q(s, i, ms);
	}
	return (count);
}
