/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:08:59 by htrindad          #+#    #+#             */
/*   Updated: 2025/06/20 20:29:09 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	*counter(void)
{
	static size_t	counter = 0;

	return (&counter);
}

int	case_free(bool is_parent, char **env, t_ms *ms)
{
	if (is_parent)
		return (*es());
	ret(ms);
	clean_ms(ms);
	free_args(env);
	exit(*es());
	return (*es());
}

size_t	breaker(char const *s, size_t i, char **cases, char *c)
{
	bool	breaker;
	char	q;

	breaker = false;
	q = 0;
	while (s[i] && !breaker)
	{
		if (s[i] == q)
			q = 0;
		if (q && mini_spec_case(s + i, cases))
		{
			breaker = true;
			*counter() = i;
			*c = q;
			break ;
		}
		if ((s[i] == '\'' || s[i] == '\"') && !q)
			q = s[i++];
		i++;
	}
	return (breaker);
}

size_t	change_sit(char const *s, char *q)
{
	while (s[*counter()] && s[*counter()] != *q)
		(*counter())++;
	(*counter())++;
	*q = 0;
	return (*counter());
}

char	**duplicator(char **arg)
{
	size_t	max;
	size_t	i;
	char	**ptr;

	max = 0;
	i = 0;
	while (arg[max])
		max++;
	ptr = ft_calloc(max + 1, sizeof(char *));
	while (i < max)
	{
		ptr[i] = ft_strdup(arg[i]);
		i++;
	}
	ptr[max] = NULL;
	return (ptr);
}
