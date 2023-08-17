/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:28:49 by mdenguir          #+#    #+#             */
/*   Updated: 2023/08/12 20:00:58 by mdenguir         ###   ########.fr       */
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
	if (c == ' ')
		return (1);
	return (0);
}

int	is_special(int c)
{
	return (c == ' ' || c == '<' || c == '>' || c == '\n'
		|| c == '$' || c == '|' || c == '\'' || c == '"');
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	if (!s2)
		return (-1);
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

char	*ft_strjoin(char *s1, char c)
{
	char	*joined;
	int		index;
	int		s1_len;

	s1_len = ft_strlen(s1);
	joined = (char *)malloc(s1_len + 2);
	if (!joined)
		return (NULL);
	index = 0;
	while (s1 && s1[index])
	{
		joined[index] = s1[index];
		index++;
	}
	joined[index++] = c;
	joined[index] = '\0';
	free(s1);
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