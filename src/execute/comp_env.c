/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:59:53 by mely-pan          #+#    #+#             */
/*   Updated: 2025/08/17 20:31:06 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline size_t	envsize(t_env *env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		if (env->value == NULL)
		{
			env = env->next;
			continue ;
		}
		i++;
		env = env->next;
	}
	return (i);
}

static char	*join_env_entry(char *env_value, char *env_key)
{
	char	*joined;

	joined = ft_calloc((ft_strlen(env_key) + ft_strlen(env_value) + 2), 1);
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, env_key, ft_strlen(env_key) + 1);
	ft_strlcat(joined, "=", ft_strlen(env_key) + 2);
	ft_strlcat(joined, env_value, ft_strlen(joined) + ft_strlen(env_value) + 1);
	return (joined);
}

static inline char	**backup(t_env *env, t_ms **ms)
{
	env = get_env(NULL);
	if (env == NULL)
		return (NULL);
	(*ms)->env = env;
	return (comp_env(env, ms));
}

char	**comp_env(t_env *env, t_ms **ms)
{
	char	**ptr;
	size_t	i;

	i = envsize(env);
	if (!i)
		return (backup(env, ms));
	ptr = ft_calloc(i + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	while (env)
	{
		if (!env->key || !env->value)
		{
			env = env->next;
			continue ;
		}
		ptr[i] = join_env_entry(env->value, env->key);
		if (!ptr[i++])
			return (free_args(ptr), NULL);
		env = env->next;
	}
	ptr[i] = NULL;
	return (ptr);
}
