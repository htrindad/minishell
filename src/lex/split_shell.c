/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:57:06 by mely-pan          #+#    #+#             */
/*   Updated: 2025/04/18 18:32:55 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	ft_safe_allocate(char ***array, size_t count, char const *s)
{
	size_t	i;
	size_t	itr;
	size_t	len;

	i = 0;
	itr = 0;
	len = 0;
	*array = ft_calloc(count + 1, sizeof(char *));
	if (*array == NULL)
		return (true);
	(*array)[count] = NULL;
	while (itr < count)
	{
		while (s[len] && s[len] != ' ')
			len++;
		(*array)[itr] = ft_substr(s, i, len - i);
		if ((*array)[itr++] == NULL)
			return (free_args(*array), true);
		i = ++len;
	}
	return (false);
}

bool	sub(char ***array, char const *s, t_ms *ms, size_t *len)
{
	size_t	i;
	size_t	count;

	i = *len;
	while (s[i] == ' ')
		i++;
	if (!s[i])
		return (*len += i, false);
	count = ft_count_words(s + i, ms);
	if (ft_safe_allocate(array, count, s + i))
		return (em("Error\nMalloc Fail.\n", ms), true);
	*len += i;
	return (false);
}

static bool	ft_filling_arr(char ***array, char const *s, t_ms *ms, size_t count)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (i < count)
		if (sub(&array[i++], s, ms, &len))
			return (true);
	array[i] = NULL;
	return (false);
}

char	***ft_split_shell(t_ms *shell)
{
	char	***array;
	char	*new_s;
	size_t	count;

	if (!shell->input)
		return (NULL);
	count = count_cases(shell->input, shell);
	array = ft_calloc(count + 1, sizeof(char **));
	if (!array)
		return (NULL);
	array[count] = NULL;
	if (has_env_var(shell->input))
	{
		new_s = handle_env_var(shell);
		if (!new_s)
			return (NULL);
		if (ft_filling_arr(array, new_s, shell, count))
			return (free(new_s), NULL);
		free(new_s);
	}
	else if (ft_filling_arr(array, shell->input, shell, count))
		return (NULL);
	return (array);
}
