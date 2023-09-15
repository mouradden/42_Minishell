/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:22:51 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/15 12:02:26 by yoamzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	expand_word(t_env *env)
{
	t_elem	*cursor;
	char	*join;
	int		i;

	cursor = env->elem;
	while (cursor)
	{
		if (cursor && ((cursor->type == VAR
					&& is_contains(cursor->content, '=') > -1)
				|| cursor->type == WORD)
			&& (check_dollar(cursor->content) > -1))
		{
			join = "";
			i = check_dollar(cursor->content);
			if (cursor->content[i + 1] && cursor->content[i + 1] == '?')
			{
				free(cursor->content);
				cursor->content = ft_strdup(ft_itoa(gl_exit_status));
				break ;
			}
			expand_word_sub(env, cursor, &join, &i);
		}
		cursor = cursor->next;
	}
}

void	expand_word_sub(t_env *env, t_elem *cursor, char **join, int *i)
{
	int		p;
	int		j;
	char	*word;

	p = 0;
	if (*i != 0)
		*join = ft_strjoin(*join, extract_word(cursor->content, &p, *i));
	j = *i;
	while (cursor && cursor->content[j] != is_special(cursor->content[j])
		&& cursor->content[j] != '=')
		j++;
	word = extract_word(cursor->content, i, j - *i);
	if (!ft_get_env(env, &word[1]))
		*join = ft_strjoin(*join, "");
	else
		*join = ft_strjoin(*join, ft_get_env(env, &(word[1])));
	free(word);
	j = *i;
	while (cursor->content[j])
		j++;
	*join = ft_strjoin_2(*join, extract_word(cursor->content, i, j - *i));
	free(cursor->content);
	cursor->content = *join;
}


void	free_and_assign(char *s, char *conntent)
{
	free(s);
	s = ft_strdup(conntent);
}

void	expand_normal_state(t_env *env, t_elem *cursor)
{
	char	*var;

	if (cursor && !ft_strcmp(cursor->content, "$?"))
	{
		// free(cursor->content);
		// cursor->content = ft_strdup(ft_itoa(gl_exit_status));
		free_and_assign(cursor->content, ft_itoa(gl_exit_status));
	}
	else
	{
		if (cursor->content[1] >= '0' && cursor->content[1] <= '9')
		{
			// free(cursor->content);
			// cursor->content = ft_strdup(&cursor->content[2]);
			free_and_assign(cursor->content, &cursor->content[2]);
		}
		else if (cursor && !ft_get_env(env, &(cursor->content[1])))
		{
			// free(cursor->content);
			// cursor->content = ft_strdup("");
			free_and_assign(cursor->content, "");
		}
		else
		{
			var = ft_get_env(env, &(cursor->content[1]));
			free(cursor->content);
			cursor->content = remove_spaces(var);
		}
	}
}

void	expand_dquote_state(t_env *env, t_elem *cursor)
{
	char	*var;

	if (cursor && !ft_strcmp(cursor->content, "$?"))
	{
		// free(cursor->content);
		// cursor->content = ft_strdup(ft_itoa(gl_exit_status));
		free_and_assign(cursor->content, ft_itoa(gl_exit_status));
	}
	else
	{
		if (cursor->content[1] >= '0' && cursor->content[1] <= '9')
		{
			// free(cursor->content);
			// cursor->content = ft_strdup(&cursor->content[2]);
			free_and_assign(cursor->content, &cursor->content[2]);
		}
		else if (cursor && !ft_get_env(env, &(cursor->content[1])))
		{
			// free(cursor->content);
			// cursor->content = ft_strdup("");
			free_and_assign(cursor->content, "");
		}
		else
		{
			var = ft_get_env(env, &(cursor->content[1]));
			// free(cursor->content);
			// cursor->content = ft_strdup(var);
			free_and_assign(cursor->content, var);
		}
	}
}
