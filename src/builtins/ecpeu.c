/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecpeu.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:35:03 by htrindad          #+#    #+#             */
/*   Updated: 2025/05/10 18:54:51 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quit(t_ms *ms)
{
	ms->running = false;
	printf("exit\n");
	return (0);
}

int	env(t_ms *ms)
{
	t_env	*env;

	env = ms->env;
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int	pwd(t_ms *ms)
{
	t_env	*env;

	env = ms->env;
	while (1)
	{
		if (!env || !ft_strncmp(env->key, "PWD", 3))
			break ;
		env = env->next;
	}
	if (env == NULL)
		return (1);
	printf("%s\n", env->value);
	return (0);
}

int	change_dir(t_ms *ms)
{
	char	c[PATH_MAX];
	t_token	*tok;

	tok = ms->tokens;
	if (tok->value[1] == NULL)
	{
		tok->value[1] = get_home(ms->env);
		if (tok->value == NULL)
			return (printf("cd: HOME not set\n"));
	}
	getcwd(c, sizeof(c));
	if (chdir(tok->value[1]) < 0)
	{
		if (!tok->value[1][0])
			return (1);
		perror(tok->value[1]);
		return (1);
	}
	set_pwd(c, sizeof(c), ms->env, ms);
	return (0);
}

int	unset(t_ms *ms)
{
	int		i;
	char	**arg;
	bool	ret;

	ret = 0;
	i = 0;
	arg = ms->tokens->value + 1;
	while (arg[i])
	{
		if (check_unst(arg[i]))
		{
			i++;
			ret = 1;
			continue ;
		}
		rm_env(&ms->env, arg[0]);
		i++;
	}
	return (ret);
}
