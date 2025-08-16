/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecpeu.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:35:03 by htrindad          #+#    #+#             */
/*   Updated: 2025/08/16 21:46:32 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quit(t_ms *ms)
{
	long long	num;
	char		**args;

	num = 0;
	args = ms->tokens->value;
	ms->running = false;
	printf("exit\n");
	if (args[1])
	{
		if (args[2])
			return (perror("Too many arguments"), 1);
		num = ft_atoll(args[1]);
		if (!num && !ft_isdigit(args[1][0]))
			return (perror("Non string as argument"), 2);
		if (num < INT_MIN || num > INT_MAX)
			return (perror("number goes out of bounds"), 2);
	}
	return ((int)num);
}

int	env(t_ms *ms)
{
	t_env	*env;

	env = ms->env;
	while (env)
	{
		if (env->key && env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int	pwd(t_ms *ms)
{
	char	c[PATH_MAX];

	if (getcwd(c, sizeof(c)))
	{
		free(ms->c_pwd);
		ms->c_pwd = ft_strdup(c);
	}
	printf("%s\n", ms->c_pwd);
	return (0);
}

int	change_dir(t_ms *ms)
{
	char	c[PATH_MAX];
	t_token	*tok;

	tok = ms->tokens;
	if (tok->value[1] == NULL)
		if (rearchitect(&tok->value, ms))
			return (printf("cd: HOME not set, or alloc failure\n"));
	if (tok->value[2])
		return (perror("Too many arguments."), 1);
	if (tok->value[1][0] == '~' && tok->value[1][1] == '/')
		tok->value[1] = tilt(tok->value[1], ms->home);
	if (getcwd(c, sizeof(c)) == NULL || chdir(tok->value[1]) < 0)
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
		rm_env(&ms->env, arg[i]);
		i++;
	}
	return (ret);
}
