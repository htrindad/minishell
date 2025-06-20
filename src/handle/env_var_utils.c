/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:44:05 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/19 17:11:35 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*var_cases(t_ms *shell, char *input, int *i)
{
	char	*tmp;

	if (input[*i] == '?')
		tmp = ft_itoa(*es());
	else if (input[*i] == '$')
		tmp = ft_itoa(shell->shell_pid);
	else if (ft_isalpha(input[*i]) || input[*i] == '_')
		tmp = extract_env_var(shell, input, i);
	else
		tmp = ft_strdup("$");
	return (tmp);
}

bool	has_env_var(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			continue ;
		}
		else if (s[i] == '$')
		{
			i++;
			if (s[i] == '?' || s[i] == '$')
				return (true);
			if (ft_isalpha(s[i]) || s[i] == '_')
				return (true);
		}
		if (s[i])
			i++;
	}
	return (false);
}

char	*get_env_value(t_env *env, char *env_var)
{
	t_env	*tmp;
	char	*env_value;

	tmp = env;
	while (tmp)
	{
		if (tmp->key && !ft_strncmp(tmp->key, env_var, ft_strlen(env_var)))
		{
			if (tmp->value == NULL)
				return (NULL);
			env_value = ft_strdup(tmp->value);
			if (!env_value)
				return (NULL);
			return (env_value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*extract_env_var(t_ms *shell, char *input, int *i)
{
	char	*env_var;
	char	*tmp;
	int		j;

	j = *i;
	while (input[j] && (ft_isalnum(input[j]) || input[j] == '_'))
		j++;
	env_var = ft_substr(input, *i, j - *i);
	if (!env_var)
		return (NULL);
	tmp = get_env_value(shell->env, env_var);
	free(env_var);
	*i = j - 1;
	if (!tmp)
		return (NULL);
	return (tmp);
}
