#include "./libft.h"

static int	is_special_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

static size_t	ft_count_args(char const *s)
{
	size_t	i;
	size_t	count;
	char	inside_q;

	i = 0;
	count = 0;
	inside_q = 0;
	while (s[i++])
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		count++;
		if (s[i] == '\'' || s[i] == '\"')
			i += iterate_through_q(s, i, &inside_q);
		else
		{
			while (s[i] && s[i] != ' ' && ((!is_special_char(s[i]) || inside_q)))
				i += iterate_through_q(s, i, &inside_q);
		}
		if (is_special_char(s[i]) && !inside_q)
			i++;
	}
	return (count);
}

static int	ft_safe_allocate(char **array, int index, size_t len)
{
	array[index] = malloc(sizeof (char) * (len + 1));
	if (!array[index])
	{
		while (index > 0)
			free(array[--index]);
		free(array);
		return (0);
	}
	return (1);
}

static int	ft_filling_arr(char **array, char const *s)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	inside_q;

	i = 0;
	inside_q = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		len = 0;
		if (s[i] == '\'' || s[i] == '\"')
			len = iterate_through_q(s, i, &inside_q);
		else if (is_special_char(s[i]))
		{
			len = 1;
			if (is_special_char(s[i + 1]))
				len++;
		}
		else
			while (s[i + len] && s[i + len] != ' ' && ((!is_special_char(s[i + len]) || inside_q)))
				len += iterate_through_q(s, i, &inside_q);
		if (!ft_safe_allocate(array, j, len))
			return (0);
		ft_strlcpy(array[j], s + i, len + 1);
		j++;
		i += len;
	}
	return (1);
}

char	**ft_split_shell(char const *s)
{
	char	**array;
	size_t	args;

	if (!s)
		return (NULL);
	args = ft_count_args(s);
	array = malloc(sizeof (char *) * (args + 1));
	if (!array)
		return (NULL);
	array[args] = '\0';
	if (!ft_filling_arr(array, s))
		return (NULL);
	return (array);
}
