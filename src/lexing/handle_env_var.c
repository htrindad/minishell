#include "../../minishell.h"

// Extracts the env var from the string and returns it
//char *handle_env_var(char *s, t_env *env)
//{
//	char	*new_s;
//	char	*tmp;
//	char	*var;
//	int		i;
//
//	i = -1;
//	new_s = ft_strdup("");
//	if (!new_s)
//		return (NULL);
//	while (s[++i])
//	{
//		if (s[i] == '$' && s[i + 1])
//		{
//			if (++i && s[i] == '?')
//				var = extract_last_status();
//			else if (ft_isalpha(s[i]) || s[i] == '_')
//			{
//				tmp = extract_env_var(s, i);
//				new_s = ft_strjoin(new_s, tmp);
//				free(tmp);
//			}
//		}
//	}
//	return (new_s);
//}
//
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

char	*extract_last_status(void)
{
	char	*status;


	return (status);
}