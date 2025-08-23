/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:57:06 by mely-pan          #+#    #+#             */
/*   Updated: 2025/08/23 21:06:18 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	ft_safe_allocate(char ***array,
		t_ms *ms, size_t *len)
{
	size_t	i;
	size_t	itr;
	char	*tmp;

	i = *len;
	itr = 0;
	*array = ft_calloc(*counter() + 1, sizeof(char *));
	if (*array == NULL)
		return (true);
	(*array)[*counter()] = NULL;
	while (itr < *counter())
	{
		c_len(len, ms->input, ms->scases);
		tmp = temper(ms->input, i, *len);
		if (tmp == NULL)
			return (true);
		(*array)[itr] = trimmer(tmp);
		if ((*array)[itr++] == NULL)
			return (free_args(*array), true);
		while (ms->input[*len] && ms->input[*len] == ' ')
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

	i = *len;
	while (s[i] && (s[i] == ' ' || mini_spec_case(s + i, ms->scases)))
	{
		if (!i)
		{
			if (f_spec_case(s, &i, ms->scases))
			{
				*array = NULL;
				*len = i;
				return (false);
			}
		}
		i++;
	}
	*len = i;
	if (!s[i])
		return (false);
	if (stopper(ms, s, i))
		return (true);
	if (ft_safe_allocate(array, ms, len))
		return (em("Error\nMalloc Fail.", ms, 0), true);
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

t_info	ft_split_shell(t_ms *shell)
{
	t_info	info;
	char	*new_s;

	if (!shell->input || !ft_strncmp(shell->input, "", 1))
		return (empty_info());
	info.count = count_cases(shell->input, shell);
	if (!info.count)
		return (empty_info());
	info.ptr = ft_calloc(info.count + 1, sizeof(char **));
	if (info.ptr == NULL)
		return (empty_info());
	info.ptr[info.count] = NULL;
	if (has_env_var(shell->input))
	{
		new_s = handle_env_var(shell->input, shell);
		if (!new_s || swap_strs(&shell->input, new_s))
			return (free_pre_split(info.ptr), empty_info());
		if (ft_filling_arr(info.ptr, new_s, shell, info.count))
			return (free_pre_split(info.ptr), free(new_s), empty_info());
		free(new_s);
	}
	else if (ft_filling_arr(info.ptr, shell->input, shell, info.count))
		return (nuller(info.ptr), empty_info());
	return (info);
}
