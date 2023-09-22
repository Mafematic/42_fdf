#include "../includes/fdf.h"

int	is_whitespace(char c)
{
	if (c >= 7 && c <= 13)
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}

int	contains_number(char *s, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (s[i] >= '0' && s[i] <= '9')
			return (1);
		i++;
	}
	return (0);
}

static char	**counter(char *s, char c)
{
	int		i;
	int		count;
	char	**words;
	size_t	start;
	size_t	word_length;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != '\0' && s[i] != c)
			i++;
		word_length = i - start;
		if (word_length > 0 && contains_number(s + start, word_length))
			count++;
	}
	words = (char **)malloc(sizeof(char *) * (count + 1));
	if (!words)
		return (NULL);
	return (words);
}

void	free_words(char **words)
{
	int	i;

	i = 0;
	while (words[i] != NULL)
	{
		free(words[i]);
		words[i] = NULL;
		i++;
	}
	free(words);
}

static int	find_next_number(char *s, char c, size_t *start, size_t *end)
{
	size_t	i;

	i = *start;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		*start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		*end = i;
		if (contains_number(s + *start, *end - *start))
			return (1);
		*start = *end;
	}
	return (0);
}

static char	**fill_words(char **words, char *s, char c)
{
	size_t	start;
	size_t	end;
	size_t	j;

	start = 0;
	j = 0;
	while (find_next_number(s, c, &start, &end))
	{
		words[j] = ft_substr(s, start, end - start);
		if (!words[j])
		{
			free_words(words);
			return (NULL);
		}
		j++;
		start = end;
	}
	words[j] = NULL;
	return (words);
}

char	**ft_split(char *s, char c)
{
	char	**words;

	if (!s)
		return (NULL);
	words = counter(s, c);
	if (!words)
		return (NULL);
	if (!fill_words(words, s, c))
	{
		free(words);
		return (NULL);
	}
	return (words);
}
