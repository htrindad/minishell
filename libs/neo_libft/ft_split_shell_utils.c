#include "./libft.h"

size_t	iterate_through_q(const char *s, size_t i, char *quote_type)
{
	size_t	start;

	start = i;
	if (s[i] == '\'' || s[i] == '\"')
	{
		*quote_type = s[i++];
		while (s[i] && s[i] != *quote_type)
			i++;
		*quote_type = 0;
	}
	if(s[i])
		i++;
	return (i - start);
}