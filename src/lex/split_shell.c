/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:57:06 by mely-pan          #+#    #+#             */
/*   Updated: 2025/04/14 13:00:33 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	ft_safe_allocate(char **array, int index, size_t len)
{
	array[index] = malloc(len + 1); //This is using malloc to avoid 'strlcpy' to be interrupted due to the '\0'
	if (!array[index])
	{
		while (index > 0)
			free(array[--index]);
		free(array);
		return (true);
	}
	return (false);
}

static bool	ft_filling_arr(char ***array, char const *s, t_ms *ms) //This function needs a serious rework, as it's working with a 'new_s' string, which I can only assume that it's for the purpose of a 'env_var', I have to study this func and rework the whole structure.
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
	char	***array;
	char	*new_s; //wtf?

	if (!shell->input)
		return (NULL);
	words = op_funcs(array, shell);
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
