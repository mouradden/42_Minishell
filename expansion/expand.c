/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:22:51 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/25 11:33:59 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand(t_env *env)
{
	t_elem		*cursor;

	expand_word(env);
	cursor = env->elem;
	while (cursor)
	{
		while (cursor && cursor->type != VAR)
			cursor = cursor->next;
		if (cursor && cursor->state == NORMAL
			&& check_dollar(cursor->content) > -1)
		{
			expand_normal_state(env, cursor);
		}
		else if (cursor && (cursor->state == IN_DQUOTE)
			&& check_dollar(cursor->content) > -1)
		{
			expand_dquote_state(env, cursor);
		}
		if (cursor)
			cursor = cursor->next;
	}
}

int	count_dollar(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

void	expand_word(t_env *env)
{
	t_elem	*cursor;
	char	*join;
	int		i;

	cursor = env->elem;
	while (cursor)
	{
		if (cursor && ((cursor->type == VAR
					&& contains(cursor->content, '=') > -1)
				|| cursor->type == WORD)
			&& (check_dollar(cursor->content) > -1))
		{
			join = NULL;
			i = check_dollar(cursor->content);
			if (cursor->content[i + 1] && cursor->content[i + 1] == '?')
			{
				free(cursor->content);
				cursor->content = ft_strdup(ft_itoa(g_exit_status));
				break ;
			}
			else if (count_dollar(cursor->content) == 1 && cursor->content[1])
				expand_word_sub(env, cursor, &join, &i);
		}
		cursor = cursor->next;
	}
}

void	expand_word_sub(t_env *env, t_elem *cursor, char **join, int *i)
{
	int		j;
	char	*word;
	char	*help;

	if (*i != 0)
		*join = ft_strjoin_2(*join, extract_word_1(cursor->content, *i));
	j = *i + 1;
	while (cursor && cursor->content[j]
		&& cursor->content[j] != '=' && cursor->content[j] != '$')
		j++;
	word = extract_word(cursor->content, i, j - *i);
	help = *join;
	if (word[1] && !ft_get_env(env, &word[1]))
		*join = ft_strjoin(*join, "");
	else if (word[1] && ft_get_env(env, &word[1]))
		*join = ft_strjoin(*join, ft_get_env(env, &(word[1])));
	free(help);
	free(word);
	j = *i - 1;
	while (cursor->content[++j])
		;
	*join = ft_strdup(ft_strjoin_2(*join,
				extract_word(cursor->content, i, j - *i)));
	free(cursor->content);
	cursor->content = *join;
}

void	free_and_assign(char *s, char *content)
{
	free(s);
	s = content;
}
