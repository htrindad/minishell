/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:04 by mely-pan          #+#    #+#             */
/*   Updated: 2025/05/31 20:12:29 by htrindad         ###   ########.fr       */
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

static void	add_back(t_env **head, t_env *new)
{
	t_env	*last;

	if (head)
	{
		if (*head)
		{
			last = *head;
			while (last->next)
				last = last->next;
			last->next = new;
			new->prev = last;
		}
		else
			*head = new;
	}
}

bool	add_env(t_env **head, char *env)
{
	t_env	*new;
	char	*equal_sign;

	equal_sign = ft_strchr(env, '=');
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (true);
	new->next = NULL;
	if (equal_sign)
		new->key = ft_substr(env, 0, ft_strlen(env) - ft_strlen(equal_sign));
	else
		new->key = ft_strdup(env);
	if (!new->key)
		return (free(new), false);
	if (equal_sign == NULL)
		new->value = NULL;
	else
		new->value = ft_strdup(equal_sign + 1);
	add_back(head, new);
	while ((*head)->prev)
		*head = (*head)->prev;
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
	t_env	*curr;

	if (!head || !*head || !arg)
		return (true);
	curr = *head;
	while (curr)
	{
		if (!ft_strncmp(curr->key, arg, ft_strlen(arg)))
		{
			rm_finisher(curr, head);
			break ;
		}
		curr = curr->next;
	}
	return (false);
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
