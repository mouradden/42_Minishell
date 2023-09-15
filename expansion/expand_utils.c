/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:24:24 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/15 16:10:35 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_env(t_env *env, char *title)
{
	t_envp	*cursor;

	cursor = env->envp;
	while (cursor && cursor->title && title && ft_strcmp(cursor->title, title))
		cursor = cursor->next;
	if (cursor && cursor->title && title && !ft_strcmp(cursor->title, title))
		return (cursor->content);
	return (NULL);
}

char	*remove_spaces(char *str)
{
	int		i;
	int		index;
	char	*result;

	i = 0;
	index = 0;
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i] && str[i] == ' ')
		i++;
	fill_without_spaces(str, &i, &result, &index);
	result[index] = '\0';
	return (result);
}

void	fill_without_spaces(char *str, int *i, char **result, int *index)
{
	while (str[*i])
	{
		if (str[*i] && str[*i] != ' ')
		{
			(*result)[*index] = str[*i];
			(*index)++;
			(*i)++;
		}
		else if (str[*i] && str[*i] == ' ')
		{
			while (str[*i] && str[*i] == ' ')
				(*i)++;
			if (str[*i])
			{
				(*result)[*index] = ' ';
				(*index)++;
			}
		}
	}
}
