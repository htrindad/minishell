/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:57:01 by mely-pan          #+#    #+#             */
/*   Updated: 2025/08/16 21:44:48 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	gnq(size_t *len, char const *s)
{
	char const	qt = s[(*len)++];

	while (s[*len] != qt)
		(*len)++;
	if (!s[*len])
		perror("Unclosed quotes.");
	if (s[*len] != ' ')
		while (s[*len] && s[*len] != ' ')
			(*len)++;
	return (*len);
}

void	c_len(size_t *len, char const *s, char **cases)
{
	while (s[*len] && s[*len] != ' ' && !mini_spec_case(s + *len, cases))
	{
		if (s[*len] == '\'' || s[*len] == '\"')
			*len = gnq(len, s);
		else
			(*len)++;
	}
}

size_t	spec_case(char const *sub, t_ms *ms, size_t *l, size_t y)
{
	int		i;

	if (ms->cas)
		ms->cas = 2;
	if (l)
		*l = 0;
	while (sub[y])
	{
		i = -1;
		while (++i < 5)
		{
			if (ft_strlen(sub + y) >= ft_strlen(ms->scases[i])
				&& !ft_strncmp(sub + y, ms->scases[i],
					ft_strlen(ms->scases[i])))
			{
				if (l)
					*l = y;
				if (ms->cas)
					ms->cas = 1;
				return (y);
			}
		}
		y++;
	}
	return (0);
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
		if (!s[i] || s[i] == '\"' || s[i] == '\'')
			return (em("Error\nUnclosed quotes", ms, 1), ft_strlen(s + start));
		quote_type = 0;
		while (s[i] && s[i] != ' ')
			i++;
	}
	if (s[i] && s[i] != ' ')
		i++;
	return (i - start);
}

size_t	stress(char const *s, t_ms *ms, size_t *tmp, size_t *l)
{
	size_t	count;
	size_t	i;

	count = 1;
	i = 0;
	while (!*tmp && s[i])
	{
		*tmp += spec_case(s, ms, l, i);
		count += !i++ && mini_spec_case(ms->input, ms->scases);
	}
	return (count);
}
