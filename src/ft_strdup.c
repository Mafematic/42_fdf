#include "../includes/fdf.h"

char	*ft_strdup(char *s)
{
	size_t	len;
	char	*cpy;
	size_t	i;

	len = ft_strlen(s);
	cpy = (char *)malloc(sizeof(char) * len + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
