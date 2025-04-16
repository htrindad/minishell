/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:00:00 by htrindad          #+#    #+#             */
/*   Updated: 2025/04/16 19:29:52 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			tmp += spec_case(s, ms->scases, NULL, i);
			i++;
		}
		if (!s[i])
			break;
		count++;
		while (s[i])
		{
			tmp += spec_case(s, ms->scases, NULL, i);
			count += tmp;
			i += tmp;
		}
	}
	return (count);
}

//static size_t	ft_count_words(char const *s, t_ms *ms, size_t max)
//{
//	size_t	i;
//	size_t	count;
//	char	*tmp;
//
//	i = 0; //len
//	count = 0; // space
//	while (s[i] && i < max)
//	{
//		while (s[i] == ' ')
//			i++;
//		if (!s[i])
//			break ;
//		count++;
//		tmp = ft_substr(s, i, 2);
//		if (is_special_char(s[i]) || s[i] == '\'' || s[i] == '\"')
//			i += iteration_cases(s, i, ms->scases, ms);
//		else
//		{
//			while (s[i] && s[i] != ' ' && !is_special_char(s[i]))
//				i += iterate_through_q(s, i, ms);
//		}
//		free(tmp);
//	}
//	return (count);
//}
//
//static char	**fill(char const *s, t_ms *ms)
//{
//	size_t	i;
//	size_t	count;
//	char	**ptr;
//
//	i = spec_case(s, ms->scases, NULL, 0);
//	count = ft_count_words(s, ms, i);
//	ptr = ft_calloc(count + 1, sizeof(char *));
//	if (ptr == NULL || sub(ptr, s, ms))
//		return (em("Error\nMalloc fail.\n", ms), NULL);
//}

size_t	op_funcs(char ***array, t_ms *ms)
{
	size_t	count;
	size_t	i;
	size_t	l;
	size_t	arr;

	i = 0;
	l = 0;
	arr = 0;
	count = count_cases(ms->input, ms);
	array = ft_calloc(count + 1, sizeof(char **));
	if (array == NULL)
		return (em("Error\nMalloc failed.\n", ms), 0);
//	while (ms->input[i])
//	{
//		i += iteration_cases(ms->input, i, ms->scases, ms);
//		array[arr++] = fill(ms->input + i, ms);
//		l = i;
//	}
	array[count] = NULL;
	return (count);
}
