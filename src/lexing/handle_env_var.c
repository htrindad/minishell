#include "../../minishell.h"

// returns a positive int if the character next to the $ is a valid
// character for an env var (alphanumeric, '_' or '?' just after the $)
// Return 0 if it does not contain a valid env var
int	has_env_var(const char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			while (s[i] && s[i] != '\'')
				i++;
		else if (s[i] == '$')
		{
			i++;
			if (s[i] == '?')
				return (1);
			if (ft_isalpha(s[i]) || s[i] == '_')
				return (1);
		}
		i++;
	}
	return (0);
}

char *ft_strjoin_free(char *s1, char *s2)
{
    char *joined = ft_strjoin(s1, s2);
    free(s1);
    return (joined);
}

char	*get_env_value(t_env *env, char *env_var)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->key && !ft_strncmp(tmp->key, env_var, ft_strlen(env_var)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*extract_env_var(char *new_s, t_ms *shell, int *i)
{
	char	*env_var;
	char	*env_value;
	char	*tmp;
	int		j;

	j = *i;
	while (shell->input[j] && (ft_isalnum(shell->input[j]) || shell->input[j] == '_'))
		j++;
	env_var = ft_substr(shell->input, *i, j - *i);
	if (!env_var)
		return (NULL);
	env_value = get_env_value(shell->env, env_var);
	if (!env_value)
		return (free(env_var), NULL);
	tmp = ft_strjoin(new_s, get_env_value(shell->env, env_var));
	free(env_var);
	if (!tmp)
		return (NULL);
	*i = j - 1;
	return (tmp);
}
// Extracts the env var from the string and returns it
char *handle_env_var(t_ms *shell)
{
	char	*new_s;
	char	*tmp;
	char	str[2];
	int		i;

	i = 0;
	new_s = ft_strdup("");
	if (!new_s)
		return (NULL);
	while (shell->input[i])
	{
		if (shell->input[i] == '$' && shell->input[i + 1])
		{
			i++;
			if (shell->input[i] == '?')
				tmp = ft_itoa(shell->last_status);
			else if (ft_isalpha(shell->input[i]) || shell->input[i] == '_')
				tmp = extract_env_var(new_s, shell, &i);
			else
				tmp = ft_strdup("$");
			if (!tmp)
				return (free(new_s), NULL);
			new_s = ft_strjoin_free(new_s, tmp);
		}
		else
		{
			str[0] = shell->input[i];
			str[1] = '\0';
			new_s = ft_strjoin_free(new_s, str);
		}
		i++;
	}
	return (new_s);
}
