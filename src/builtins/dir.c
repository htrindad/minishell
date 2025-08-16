/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:22:09 by htrindad          #+#    #+#             */
/*   Updated: 2025/08/16 21:26:16 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline t_env	*create_pwd(t_env *env)
{
	char	c[PATH_MAX];
	char	*path;

	path = ft_calloc(PATH_MAX + 5, 1);
	if (path == NULL)
		return (NULL);
	getcwd(c, sizeof(c));
	ft_strlcpy(path, "PWD=", 5);
	ft_strlcat(path, c, 5 + PATH_MAX);
	if (add_env(&env, path))
		return (free(path), NULL);
	free(path);
	return (env);
}

t_env	*get_pwd(t_env *env)
{
	t_env	*first;

	first = env;
	while (env)
	{
		if (!ft_strncmp(env->key, "PWD", 3))
			break ;
		env = env->next;
	}
	if (env == NULL)
		return (create_pwd(first));
	return (env);
}

char	*get_home(t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(env->key, "HOME", 4))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static inline void	ch_oldpwd(char *c, t_env *env, t_ms *ms)
{
	while (env)
	{
		if (!ft_strncmp(env->key, "OLDPWD", 6))
		{
			free(env->value);
			env->value = ft_strdup(c);
			if (env->value == NULL)
				em("Error\nMalloc Fail.\n", ms, 0);
			break ;
		}
		env = env->next;
	}
}

void	set_pwd(char *c, size_t size, t_env *env, t_ms *ms)
{
	t_env	*pwd;

	pwd = get_pwd(env);
	if (pwd == NULL)
		em("Error\nMalloc Fail.\n", ms, 0);
	ch_oldpwd(c, env, ms);
	getcwd(c, size);
	free(pwd->value);
	pwd->value = ft_strdup(c);
	if (pwd->value == NULL)
		em("Error\nMalloc Fail.\n", ms, 0);
}
