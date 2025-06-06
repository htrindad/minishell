/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:16 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/04 20:08:53 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// returns a positive int if the character next to the $ is a valid
// character for an env var (alphanumeric, '_' or '?' just after the $)
// Return 0 if it does not contain a valid env var
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

// Extracts the env var from the string and returns it
static char	*handle_dollar_case(t_ms *shell, char *input, int *i, char *new_s)
{
	char	*tmp;

	(*i)++;
	tmp = var_cases(shell, input, i);
	if (!tmp)
		return (free(new_s), NULL);
	new_s = ft_strjoin_free(new_s, tmp);
	free(tmp);
	return (new_s);
}

char	*conc_char(char c)
{
	char	str[2];

	str[0] = c;
	str[1] = 0;
	return (ft_strdup(str));
}

static char	*handle_regular_char(char c, char *new_s)
{
	char	*tmp;

	tmp = conc_char(c);
	if (!tmp)
		return (free(new_s), NULL);
	new_s = ft_strjoin_free(new_s, tmp);
	free(tmp);
	return (new_s);
}

char	*handle_env_var(char *input, t_ms *shell)
{
	char	*new_s;
	int		i;

	i = 0;
	new_s = ft_strdup("");
	if (!new_s)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1])
			new_s = handle_dollar_case(shell, input, &i, new_s);
		else
			new_s = handle_regular_char(input[i], new_s);
		if (!new_s)
			return (NULL);
		i++;
	}
	return (new_s);
}
