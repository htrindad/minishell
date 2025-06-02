#include "../minishell.h"

static inline size_t	envsize(t_env *env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**comp_env(t_env *env)
{
	char	**ptr;
	char	*tmp;
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
		if (env->key == NULL || env->value == NULL)
		{
			env = env->next;
			continue ;
		}
		tmp = ft_calloc(ft_strlen(env->key) + ft_strlen(env->value) + 2, sizeof(char));
		if (tmp == NULL)
			return (free_args(ptr), NULL);
		ft_strlcpy(tmp, env->key, ft_strlen(env->key) + 1);
		ft_strlcat(tmp, "=", ft_strlen(env->key) + 2);
		ft_strlcat(tmp, env->value, ft_strlen(tmp) + ft_strlen(env->value) + 1);
		ptr[i++] = tmp;
		env = env->next;
	}
	ptr[i] = NULL;
	return (ptr);
}
