/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:38:04 by htrindad          #+#    #+#             */
/*   Updated: 2025/06/07 17:32:35 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	stopper(size_t *counter, t_ms *ms, char const *s, size_t i)
{
	*counter = ft_count_words(s + i, ms);
	if (!ms->running)
		return (true);
	return (false);
}

static bool	quoter(char const *s)
{
	size_t	i;
	char	q;

	q = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			q = s[i++];
			while (s[i] != q && s[i])
				i++;
			if (s[i] == q)
				return (true);
		}
		if (!s[i] && q)
			break ;
		i++;
	}
	return (false);
}

static size_t	true_size(char const *s, size_t i, size_t len)
{
	size_t	j;
	char	qo;

	j = 0;
	qo = 0;
	while (i < len && s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && quoter(s + i))
		{
			qo = s[i];
			i++;
			continue ;
		}
		else if (qo == s[i])
		{
			i++;
			qo = 0;
			continue ;
		}
		j++;
		i++;
	}
	return (++j);
}

static inline size_t	q_case(char const *s, char *tmp, size_t *i, \
		size_t r_size)
{
	size_t	j;
	char	q;

	j = 0;
	q = s[*i];
	if (!quoter(s + (*i)++))
		tmp[j++] = q;
	else
		while (s[*i] && s[*i] != q && j < r_size - 1)
			tmp[j++] = s[(*i)++];
	(*i)++;
	return (j);
}

char	*temper(char const *s, size_t i, size_t len)
{
	char	*tmp;
	size_t	r_size;
	size_t	j;

	if (!quoter(s + i))
		return (ft_substr(s, i, len - i));
	r_size = true_size(s, i, len);
	tmp = ft_calloc(r_size + 1, 1);
	if (tmp == NULL)
		return (NULL);
	tmp[r_size] = 0;
	j = 0;
	while (j < r_size - 1)
	{
		if (s[i] == '\'' || s[i] == '\"')
			j += q_case(s, tmp + j, &i, r_size - j);
		else
			tmp[j++] = s[i++];
	}
	return (tmp);
}
