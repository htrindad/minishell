/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:55:58 by htrindad          #+#    #+#             */
/*   Updated: 2025/08/17 20:40:26 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline t_env	*return_it(char **ptr)
{
	size_t	i;
	t_env	*new;

	new = NULL;
	i = 0;
	while (i < 3)
	{
		if (add_env(&new, ptr[i]))
		{
			free_env(new);
			free_args(ptr);
			return (NULL);
		}
		i++;
	}
	return (free_args(ptr), new);
}

t_env	*empty_env(void)
{
	char	**ptr;
	char	c[PATH_MAX];

	if (getcwd(c, sizeof(c)) == NULL)
		return (NULL);
	ptr = ft_calloc(4, sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	ptr[0] = ft_calloc(ft_strlen(c) + 6, 1);
	if (ptr[0] == NULL)
		return (free(ptr), NULL);
	(ft_strlcpy(ptr[0], "PWD", 4), ft_strlcat(ptr[0], "=", 6));
	ft_strlcat(ptr[0], c, ft_strlen(c) + 6);
	ptr[1] = ft_strdup("SHLVL=0");
	if (ptr[1] == NULL)
		return (free(ptr[0]), free(ptr), NULL);
	ptr[2] = ft_strdup("_=/usr/bin/env");
	if (ptr[2] == NULL)
		return (free_args(ptr), NULL);
	return (return_it(ptr));
}

void	rm_finisher(t_env *curr, t_env **head)
{
	t_env	*prev;
	t_env	*next;

	prev = curr->prev;
	next = curr->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (curr == *head)
		*head = next;
	free(curr->key);
	free(curr->value);
	free(curr);
}
