#include "minishell.h"

//get_env() function is used to get the environment variables from the envp
//when using execve() function, I will need to use the environment variables
//but execve() requires a char **envp, so I need to convert the linked list into
//a char **envp. (I will do that in another function furthermore the project) and
//use it inside each forked process. (so it's clean and doesn't affect the parent process)
static int	add_env(t_env **head, char *env)
{
	t_env	*new;
	char	*equal_sign;

	equal_sign = ft_strchr(env, '=');
	new = ft_calloc(1, sizeof(t_env));
	if (!new || !equal_sign)
		return (0);
	new->next = NULL;
	new->key = ft_substr(env, 0, ft_strlen(env) - ft_strlen(equal_sign));
	if (!new->key)
		return (free(new), 0);
	new->value = ft_strdup(equal_sign + 1);
	if (!new->value)
		return (free(new->key), free(new), 0);
	ft_lstadd_back((t_list **)head, (t_list *)new);
	return (1);
}


t_env *get_env(char **env)
{
	t_env	*new;
	int		i;

	i = 0;
	new = NULL;
	while (env[i])
	{
		if (!add_env(&new, env[i]))
		{
			free_env(new);
			ft_putstr_fd("Error:\nMalloc failed", 2);
			exit (1);
		}
		i++;
	}
	return (new);
}

//typedef struct s_data
//{
//	char *key;
//	char *value;
//	struct s_data *next;
//} t_data;
//
//t_data *d()
//{
//	static t_data d;
//	return (&d);
//}
//=======================================
//int main(int ac, char **av, char **env)
//{
	//	t_env *env_list;
//	t_env *env_list_ptr;
//
//	(void)ac;
//	(void)av;
//	env_list_ptr = get_env(env);
//	env_list = env_list_ptr;
//	while (env_list)
//	{
	//		printf("Key: %s\nValue: %s\n", env_list->key, env_list->value);
	//		env_list = env_list->next;
	//	}
	//	free_env(env_list_ptr);
	//	return (0);
//}
