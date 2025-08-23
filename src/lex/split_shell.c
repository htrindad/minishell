/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:57:06 by mely-pan          #+#    #+#             */
/*   Updated: 2025/08/23 17:48:40 by htrindad         ###   ########.fr       */
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
		if (!i || (*len && spec_case_middle(s, i, ms->scases)))
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
	t_info	arg;
	char	*new_s;

	if (!shell->input || !ft_strncmp(shell->input, "", 1))
		return (empty_spli());
	arg.count = count_cases(shell->input, shell);
	if (!arg.count)
		return (empty_spli());
	arg.ptr = ft_calloc(arg.count + 1, sizeof(char **));
	if (arg.ptr == NULL)
		return (empty_spli());
	arg.ptr[arg.count] = NULL;
	if (has_env_var(shell->input))
	{
		new_s = handle_env_var(shell->input, shell);
		if (!new_s || swap_strs(&shell->input, new_s))
			return (free_pre_split(arg.ptr), empty_spli());
		if (ft_filling_arr(arg.ptr, new_s, shell, arg.count))
			return (free_pre_split(arg.ptr), free(new_s), empty_spli());
		free(new_s);
	}
	else if (ft_filling_arr(arg.ptr, shell->input, shell, arg.count))
		return (nuller(arg.ptr), empty_spli());
	return (arg);
}
