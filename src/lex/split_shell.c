/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:57:06 by mely-pan          #+#    #+#             */
/*   Updated: 2025/04/13 18:04:03 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	ft_safe_allocate(char **array, int index, size_t len)
{
	array[index] = malloc(sizeof(char) * (len + 1));
	if (!array[index])
	{
		while (index > 0)
			free(array[--index]);
		free(array);
		return (true);
	}
	return (false);
}

static bool	ft_filling_arr(char **array, char const *s, t_ms *ms)
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
		l = iteration_cases(s, i, ms->scases, ms);
		if (ft_safe_allocate(array, j, l))
			return (true);
		ft_strlcpy(array[j], s + i, l + 1);
		j++;
		i += l;
	}
	return (false);
}

char	***ft_split_shell(t_ms *shell)
{
	size_t	words;
	size_t	cases;
	char	***array;
	char	*new_s;

	if (!shell->input)
		return (NULL);
	words = ft_count_words(shell->input, shell);
	cases = count_cases(shell->input, shell);
	op_funcs(array, words, count);
	//array = ft_calloc(words + 1, sizeof(char *)); // Gonna operate on this function
	if (!array)
		return (NULL);
	if (has_env_var(shell->input))
	{
		new_s = handle_env_var(shell);
		if (!new_s)
			return (NULL);
		if (ft_filling_arr(array, new_s, shell))
			return (free(new_s), NULL);
		free(new_s);
	}
	else if (ft_filling_arr(array, shell->input, shell))
		return (NULL);
	array[words] = NULL;
	return (array);
}
