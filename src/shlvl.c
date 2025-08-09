/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:03:30 by htrindad          #+#    #+#             */
/*   Updated: 2025/08/09 17:29:34 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	sandwich(char const *s, size_t pos, char **cases)
{
	size_t	i;

	 i = pos - 1;
	 while (i && s[i] == ' ')
		 i--;
	 if (i)
		 return (mini_spec_case(s + i, cases));
	 return (false);
}

bool	custom_f_spec_case(char const *s, size_t i, char **cases)
{
	bool	sc;
	bool	os;

	sc = false;
	os = true;
	if (s[i] == ' ')
		os = false;
	while (s[i] == ' ' || mini_spec_case(s + i, cases))
	{
		if (s[i] != ' ')
			os = false;
		if (mini_spec_case(s + i, cases))
			sc = true;
		if (sandwich(s, i, cases))
			return (false);
		i++;
	}
	if (os && i)
		i--;
	*counter() = i;
	return (sc);
}

void	shlvl_checker(char *es, t_env *new)
{
	int	lvl;

	if (!ft_strncmp(new->key, "SHLVL", 6))
	{
		lvl = ft_atoi(es + 1) + 1;
		new->value = ft_itoa(lvl);
	}
	else
		new->value = ft_strdup(es + 1);
}
