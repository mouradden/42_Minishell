/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:28:49 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/15 12:13:38 by yoamzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_special(int c)
{
	return (c == ' ' || c == '\t' || c == '<' || c == '>'
		|| c == '\n' || c == '|' || c == '\'' || c == '"');
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	if (s1 == NULL)
		ft_putstr_fd("error from strcmp s1\n", 2);
	if (s2 == NULL)
		ft_putstr_fd("error from strcmp s2\n", 2);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strdup(char *s1)
{
	char	*dst;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (s1[len])
		len++;
	dst = (char *) malloc (len * sizeof(char) + 1);
	if (!dst)
		return (NULL);
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	int		index;
	int		s1_len;

	s1_len = ft_strlen(s1);
	if (!s1 && !s2)
		return (NULL);
	joined = (char *)malloc(s1_len + ft_strlen(s2) + 1);
	// printf("joined :%p\n", joined);
	if (!joined)
		return (NULL);
	index = 0;
	while (s1 && s1[index])
	{
		joined[index] = s1[index];
		index++;
	}
	index = 0;
	while (s2 && s2[index])
	{
		joined[ft_strlen(s1) + index] = s2[index];
		index++;
	}
	joined[s1_len + index] = '\0';
	// free(s1);
	return (joined);
}

char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*joined;
	int		index;
	int		s1_len;

	s1_len = ft_strlen(s1);
	if (!s1 && !s2)
		return (NULL);
	joined = (char *)malloc(s1_len + ft_strlen(s2) + 1);
	// printf("joined :%p\n", joined);
	if (!joined)
		return (NULL);
	index = 0;
	while (s1 && s1[index])
	{
		joined[index] = s1[index];
		index++;
	}
	index = 0;
	while (s2 && s2[index])
	{
		joined[ft_strlen(s1) + index] = s2[index];
		index++;
	}
	joined[s1_len + index] = '\0';
	free(s1);
	free(s2);
	return (joined);
}

int	ft_strlen(char *s)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
