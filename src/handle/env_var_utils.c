/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:44:05 by mely-pan          #+#    #+#             */
/*   Updated: 2025/04/13 17:12:48 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*var_cases(t_ms *shell, int *i)
{
	char	*tmp;

	if (shell->input[*i] == '?')
		tmp = ft_itoa(shell->last_status);
	else if (ft_isalpha(shell->input[*i]) || shell->input[*i] == '_')
		tmp = extract_env_var(shell, i);
	else
		tmp = ft_strdup("$");
	return (tmp);
}

char	*conc_char(char c)
{
	char *tmp;
	char str[2];

	tmp = ft_strdup("");
	if (!tmp)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	ft_strjoin(tmp, str);
	return (tmp);
}
