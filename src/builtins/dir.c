/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:22:09 by htrindad          #+#    #+#             */
/*   Updated: 2025/04/22 19:53:38 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*get_pwd(t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(env->key, "PWD", 3))
			break ;
		env = env->next;
	}
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
				em("Error\nMalloc Fail.\n", ms);
		}
		env = env->next;
	}
}

void	set_pwd(char *c, t_env *env, t_ms *ms)
{
	t_env	*pwd;

	pwd = get_pwd(env);
	ch_oldpwd(c, env, ms);
	getcwd(c, sizeof(c));
	free(pwd->value);
	pwd->value = ft_strdup(c);
	if (pwd->value == NULL)
		em("Error\nMalloc Fail.\n");
}
