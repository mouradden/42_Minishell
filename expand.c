/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:22:51 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/13 20:54:20 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_word(t_env *env)
{
	t_elem	*cursor;
	char	*join;
	int		i;
	int		j;
	int		len;
	char	*word;
	char	*var;

	cursor = env->elem;
	while (cursor)
	{
		if (cursor && ((cursor->type == VAR && is_contains(cursor->content, '=') > -1)  || cursor->type == WORD)
			&& (check_dollar(cursor->content) > -1))
		{
			join = "";
			i = check_dollar(cursor->content);
			if (cursor->content[i + 1] && cursor->content[i + 1] == '?')
			{
				free(cursor->content);
				cursor->content = ft_strdup(ft_itoa(gl_exit_status));
				break;
			}
			int p = 0;
			if (i != 0)
			{
				join = ft_strjoin(join, extract_word(cursor->content, &p, i));
			}	
			j = i;
			len = 0;
			while (cursor && cursor->content[j] != is_special(cursor->content[j])
				&& cursor->content[j] != '=')
			{
				j++;
				len++;
			}
			word = extract_word(cursor->content, &i, len);
			if (!ft_get_env(env, &word[1]))
			{
				join = ft_strjoin(join, "");
			}
			else
			{
				var = ft_get_env(env, &(word[1]));
				join = ft_strjoin(join, var);
			}
			free(word);
			len = 0;
			j = i;
			while (cursor->content[j])
			{
				j++;
				len++;
			}
			join = ft_strjoin_2(join, extract_word(cursor->content, &i, len));
			free(cursor->content);
			cursor->content = join;
		}
		cursor = cursor->next;
	}
}

void	expand(t_env *env)
{
	t_elem		*cursor;
	char		*var;

	expand_word(env);
	cursor = env->elem;
	while (cursor)
	{
		while (cursor && cursor->type != VAR)
			cursor = cursor->next;
			if (cursor && cursor->state == NORMAL && check_dollar(cursor->content) > -1)
			{
				if (cursor && !ft_strcmp(cursor->content, "$?"))
				{
					free(cursor->content);
					cursor->content = ft_strdup(ft_itoa(gl_exit_status));
				}
				else
				{
					if (cursor->content[1] >= '0' && cursor->content[1] <= '9')
					{
						free(cursor->content);
						cursor->content = ft_strdup(&cursor->content[2]);
					}
					else if (cursor && !ft_get_env(env, &(cursor->content[1])))
					{
						free(cursor->content);
						cursor->content = ft_strdup("");
					}
					else
					{
						var = ft_get_env(env, &(cursor->content[1]));
						free(cursor->content);
						cursor->content = remove_spaces(var);
					}
				}
			}
			else if (cursor && (cursor->state == IN_DQUOTE) && check_dollar(cursor->content) > -1)
			{
				if (cursor && !ft_strcmp(cursor->content, "$?"))
				{
					free(cursor->content);
					cursor->content = ft_strdup(ft_itoa(gl_exit_status));
				}
				else
				{
					if (cursor->content[1] >= '0' && cursor->content[1] <= '9')
					{
						free(cursor->content);
						cursor->content = ft_strdup(&cursor->content[2]);
					}
					else if (!ft_get_env(env, &(cursor->content[1])))
					{
						free(cursor->content);
						cursor->content = ft_strdup("");
					}
					else
					{
						var = ft_get_env(env, &(cursor->content[1]));
						free(cursor->content);
						cursor->content = ft_strdup(var);
					}
				}
			}
		if (cursor)
			cursor = cursor->next;
	}
	
}

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
	while (str[i] && str[i] == ' ')
		i++;
		
	while (str[i])
	{
		if (str[i] && str[i] != ' ')
		{
			result[index] = str[i];
			index++;
			i++;
		}
		else if (str[i] && str[i] == ' ')
		{
			while (str[i] && str[i] == ' ')
				i++;
			
			if (str[i])
			{
				result[index] = ' ';
				index++;
			}
		}
	}
	result[index] = '\0';
	
	return (result);
}
