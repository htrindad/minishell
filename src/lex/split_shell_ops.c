/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:00:00 by htrindad          #+#    #+#             */
/*   Updated: 2025/04/14 12:07:00 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// The purpose of this function is to create tokens separated by special cases
static size_t	count_cases(char const *s, t_ms *ms)
{
	size_t	i;
	size_t	count;
	size_t	tmp;

	i = 0;
	count = 0;
	tmp = 0;
	while (s[i])
	{
		while (!tmp)
		{
			tmp += spec_case(s + i, ms->scases, NULL);
			i++;
		}
		if (!s[i])
			break;
		count++;
		while (s[i])
		{
			tmp += spec_case(s + i, ms->scases, NULL);
			count += tmp;
			i += tmp;
		}
	}
	return (count);
}

static size_t	ft_count_words(char const *s, t_ms *ms)
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
			i += iteration_cases(s, i, ms->scases, ms);
		else
		{
			while (s[i] && s[i] != ' ' && !is_special_char(s[i]))
				i += iterate_through_q(s, i, ms);
		}
		free(tmp);
	}
	return (count);
}

size_t	op_funcs(char ***array, t_ms *ms)
{
	size_t	count;
	size_t	words;

	count = count_cases(ms->input, ms);
	array = ft_calloc(count + 1, sizeof(char **));
	if (array == NULL)
		return (em("Error\nMalloc failed.\n", ms), 0);
	words = ft_count_words(ms->input, ms);
	return (words);
}
