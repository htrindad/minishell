/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:35:46 by htrindad          #+#    #+#             */
/*   Updated: 2025/05/08 21:03:01 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	trimmer(char ***array, char *tmp, size_t itr)
{
	char	c;

	c = *tmp;
	if (c == '\'' || c == '\"')
		(*array)[itr] = ft_strtrim(tmp, &c);
	else
		(*array)[itr] = ft_strdup(tmp);
	free(tmp);
}

size_t	count_cases(char const *s, t_ms *ms)
{
	size_t	i;
	size_t	count;
	size_t	tmp;
	size_t	l;

	i = 0;
	l = 0;
	count = 1;
	tmp = 0;
	while (!tmp && s[i])
		tmp += spec_case(s, ms->scases, &l, i++, NULL);
	if (!tmp)
		count++;
	if (!s[i])
		return (count);
	while (s[i])
	{
		tmp += spec_case(s, ms->scases, &l, i, NULL);
		if (i != tmp)
			count++;
		i += tmp;
	}
	return (count);
}

static inline bool	check(char const *s, char **cases, size_t i, t_ms *ms)
{
	char	*tmp;
	bool	cas;
	size_t	l;

	tmp = ft_substr(s, i, 2);
	cas = true;
	l = 0;
	if (tmp == NULL)
		return (em("Error\nMalloc Fail.\n", ms), 0);
	spec_case(tmp, cases, &l, 0, &cas);
	return (free(tmp), cas);
}

size_t	ft_count_words(char const *s, t_ms *ms)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		if (!check(s, ms->scases, i, ms))
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
