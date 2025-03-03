/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:39:53 by htrindad          #+#    #+#             */
/*   Updated: 2024/04/23 19:42:22 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_tcount(char const *s, char c)
{
	int	token;

	token = 0;
	while (*s)
	{
		if (*s != c)
		{
			token++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (token);
}

static int	ft_ca(char **ptr, int j)
{
	if (ptr[j] == NULL)
	{
		while (j >= 0)
		{
			free(ptr[j]);
			j--;
		}
		free(ptr);
		return (0);
	}
	return (1);
}

static int	ft_la(char const *s, char c, char **ptr, int i)
{
	int	sta;
	int	j;

	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			sta = i;
			while (s[i] && s[i] != c)
				i++;
			ptr[j] = ft_substr(s, sta, i - sta);
			if (!ft_ca(ptr, j))
				return (0);
			j++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		token;
	char	**ptr;

	if (s == NULL)
		return (NULL);
	token = ft_tcount(s, c);
	ptr = malloc((token + 1) * sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	if (!ft_la(s, c, ptr, 0))
		return (NULL);
	ptr[token] = NULL;
	return (ptr);
}
