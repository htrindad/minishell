/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:35:46 by htrindad          #+#    #+#             */
/*   Updated: 2025/06/20 15:14:29 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*trimmer(char *tmp)
{
	char	*str;

	str = ft_strdup(tmp);
	free(tmp);
	return (str);
}

static inline size_t	shorter(t_ms *ms, char const *s, size_t l, size_t tmp)
{
	size_t	count;
	size_t	i;

	i = 1;
	ms->cas = 0;
	count = stress(s, ms, &tmp, &l);
	count += !tmp || (s[0] == ' ' && tmp);
	if (!s[i])
		return (count);
	while (s[i])
	{
		tmp = spec_case(s, ms, &l, i);
		if (i < tmp)
		{
			count++;
			i = tmp;
		}
		else
			i++;
	}
	return (count);
}

size_t	count_cases(char const *s, t_ms *ms)
{
	size_t	count;

	if (all_spaces(s))
		return (0);
	if (quoter(s))
		count = ft_count_words(s, ms);
	else
		count = shorter(ms, s, 0, 0);
	return (count);
}

static int	check(char const *s, t_ms *ms, size_t i)
{
	char	*tmp;
	size_t	l;

	tmp = ft_substr(s, i, 2);
	l = 0;
	ms->cas = 2;
	if (tmp == NULL)
		return (em("Error\nMalloc Fail.\n", ms), 0);
	spec_case(tmp, ms, &l, 0);
	return (free(tmp), ms->cas);
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
		if (s[i] != '\'' && s[i] != '\"' && check(s, ms, i) == 1)
			break ;
		count++;
		if (s[i] == '\'' || s[i] == '\"')
			i += iterate_through_q(s, i, ms);
		else
			while (s[i] && s[i] != ' ' && check(s, ms, i) == 2)
				i += iterate_through_q(s, i, ms);
	}
	return (count);
}
