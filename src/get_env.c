/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:04 by mely-pan          #+#    #+#             */
/*   Updated: 2025/04/23 18:06:55 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get_env() function is used to get the environment variables from the envp
// when using execve() function, I will need to use the environment variables
// but execve() requires a char **envp,
//	so I need to convert the linked list into
// a char **envp. (I will do that in another function furthermore the project)
// and use it inside each forked process. (so it's clean and doesn't affect
// the parent process)
bool	add_env(t_env **head, char *env)
{
	t_env	*new;
	char	*equal_sign;

	equal_sign = ft_strchr(env, '=');
	new = ft_calloc(1, sizeof(t_env));
	if (!new || !equal_sign)
		return (true);
	new->next = NULL;
	new->key = ft_substr(env, 0, ft_strlen(env) - ft_strlen(equal_sign));
	if (!new->key)
		return (free(new), false);
	new->value = ft_strdup(equal_sign + 1);
	if (!new->value)
		return (free(new->key), free(new), false);
	ft_lstadd_back((t_list **)head, (t_list *)new);
	return (false);
}

void	null_case(t_env **head, t_env *tmp)
{
	tmp = *head;
	*head = (*head)->next;
	(*head)->prev = NULL;
	free(tmp);
}

bool	rm_env(t_env **head, char *arg)
{
	t_env	*tmp;

	tmp = NULL;
	while (*head)
	{
		if (!ft_strncmp((*head)->key, arg, ft_strlen(arg)))
		{
			if ((*head)->prev)
			{
				*head = (*head)->prev;
				tmp = (*head)->next;
				(*head)->next = (*head)->next->next;
				(*head)->next->prev = *head;
				free(tmp);
			}
			else
				null_case(head, tmp);
			break ;
		}
		*head = (*head)->next;
	}
}

t_env	*get_env(char **env)
{
	t_env	*new;
	int		i;

	i = 0;
	new = NULL;
	while (env[i])
	{
		if (add_env(&new, env[i]))
		{
			free_env(new);
			perror("Error:\nMalloc failed\n");
			exit(1);
		}
		i++;
	}
	return (new);
}
