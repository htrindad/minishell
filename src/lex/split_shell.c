/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:57:06 by mely-pan          #+#    #+#             */
/*   Updated: 2025/04/11 16:08:26 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_count_words(char const *s)
{
	size_t	i;
	size_t	count;
	char	*tmp;

	i = 0; //len
	count = 0; // space
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		count++;
		tmp = ft_substr(s, i, 2);
		if (is_special_char(s[i]) || s[i] == '\'' || s[i] == '\"')
			i += iteration_cases(s, i);
		else
		{
			while (s[i] && s[i] != ' ' && !is_special_char(s[i]))
				i += iterate_through_q(s, i);
		}
		free(tmp);
	}
	return (count);
}

static int	ft_safe_allocate(char **array, int index, size_t len)
{
	array[index] = malloc(sizeof(char) * (len + 1));
	if (!array[index])
	{
		while (index > 0)
			free(array[--index]);
		free(array);
		return (0);
	}
	return (1);
}

static int	ft_filling_arr(char **array, char const *s)
{
	size_t	l;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		l = iteration_cases(s, i);
		if (!ft_safe_allocate(array, j, l))
			return (0);
		ft_strlcpy(array[j], s + i, l + 1);
		j++;
		i += l;
	}
	return (1);
}

char	**ft_split_shell(t_ms *shell)
{
	size_t	words;
	char	**array;
	char	*new_s;

	if (!shell->input)
		return (NULL);
	words = ft_count_words(shell->input);
	array = ft_calloc(words + 1, sizeof(char *));
	if (!array)
		return (NULL);
	if (has_env_var(shell->input))
	{
		new_s = handle_env_var(shell);
		if (!new_s)
			return (NULL);
		if (!ft_filling_arr(array, new_s))
			return (free(new_s), NULL);
		free(new_s);
	}
	else if (!ft_filling_arr(array, shell->input))
		return (NULL);
	array[words] = NULL;
	return (array);
}
