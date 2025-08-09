/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:59:53 by mely-pan          #+#    #+#             */
/*   Updated: 2025/08/09 15:49:35 by htrindad         ###   ########.fr       */
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
	char	*dup;
	int		lvl;

	if (!ft_strncmp(env_key, "SHLVL", 6))
	{
		lvl = ft_atoi(env_value) + 1;
		dup = ft_itoa(lvl);
	}
	else
		dup = ft_strdup(env_value);
	if (dup == NULL)
		return (NULL);
	(void)lvl;
	joined = ft_calloc((ft_strlen(env_key) + ft_strlen(dup) + 2), 1);
	if (!joined)
		return (free(dup), NULL);
	ft_strlcpy(joined, env_key, ft_strlen(env_key) + 1);
	ft_strlcat(joined, "=", ft_strlen(env_key) + 2);
	ft_strlcat(joined, dup, ft_strlen(joined) + ft_strlen(dup) + 1);
	return (free(dup), joined);
}

char	**comp_env(t_env *env)
{
	char	**ptr;
	size_t	i;

	i = envsize(env);
	if (!i)
		return (NULL);
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
