#include "minishell.h"


int	count_words(const char *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count + 1);
}

int	len_word(const char *s, char c)
{
	int		count;

	count = 0;
	while (s[count] && s[count] != c)
	{
		count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char		**ptr;
	int			j;
	int			k;

	j = 0;
	ptr = (char **) malloc((count_words(s, c)) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			ptr[j] = (char *) malloc (len_word(s, c) * sizeof(char) + 1);
			k = 0;
			while (*s && *s != c)
				ptr[j][k++] = *s++;
			ptr[j++][k] = '\0';
		}
	}
	ptr[j] = NULL;
	return (ptr);
}


int main(int ac, char **av, char **envp)
{
	// void(ac);
    // void(av);
    char **cmd;
    cmd = ft_split("/bin/pwd", ' ');
    execve(cmd[0], cmd, envp);
}