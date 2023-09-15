/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:37:25 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/15 17:40:40 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	int		index;
	int		s1_len;

	s1_len = ft_strlen(s1);
	if (!s1 && !s2)
		return (NULL);
	joined = (char *)malloc(s1_len + ft_strlen(s2) + 1);
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
	free_two(s1, s2);
	return (joined);
}

void	free_two(char *s1, char *s2)
{
	free(s1);
	free(s2);
}
