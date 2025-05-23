/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:57:06 by mely-pan          #+#    #+#             */
/*   Updated: 2025/05/23 16:37:15 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	ft_safe_allocate(char ***array, size_t count, char const *s, size_t *len)
{
	size_t	i;
	size_t	itr;
	char	*tmp;

	i = *len;
	itr = 0;
	*array = ft_calloc(count + 1, sizeof(char *));
	if (*array == NULL)
		return (true);
	(*array)[count] = NULL;
	while (itr < count)
	{
		c_len(len, s);
		tmp = ft_substr(s, i, *len - i);
		if (tmp == NULL)
			return (true);
		trimmer(array, tmp, itr);
		if ((*array)[itr++] == NULL)
			return (free_args(*array), true);
		if (s[*len])
			(*len)++;
		i = *len;
	}
	return (false);
}

bool	mini_spec_case(char const *s, char **cases)
{
	int	i;

	i = -1;
	while (cases[++i])
		if (!ft_strncmp(s, cases[i], ft_strlen(cases[i])))
			return (true);
	return (false);
}

bool	sub(char ***array, char const *s, t_ms *ms, size_t *len)
{
	size_t	i;
	size_t	count;

	i = *len;
	while (s[i] && (s[i] == ' ' || mini_spec_case(s + i, ms->scases)))
		i++;
	*len = i;
	if (!s[i])
		return (false);
	count = ft_count_words(s + i, ms);
	if (ft_safe_allocate(array, count, s, len))
		return (em("Error\nMalloc Fail.\n", ms), true);
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
