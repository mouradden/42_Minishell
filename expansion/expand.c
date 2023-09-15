/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:22:51 by mdenguir          #+#    #+#             */
<<<<<<< HEAD:expansion/expand.c
/*   Updated: 2023/09/15 16:25:40 by mdenguir         ###   ########.fr       */
=======
/*   Updated: 2023/09/15 12:02:26 by yoamzil          ###   ########.fr       */
>>>>>>> 58fc06fcd125f870e055373a2db9a0d82236ea53:expand.c
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand(t_env *env)
{
	t_elem		*cursor;

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
	expand_word(env);
}

void	expand_word(t_env *env)
{
	t_elem	*cursor;
	char	*join;
	int		i;

	cursor = env->elem;
	while (cursor)
	{
		if (cursor && cursor->state != IN_QUOTE && ((cursor->type == VAR
					&& is_contains(cursor->content, '=') > -1)
				|| cursor->type == WORD)
			&& (check_dollar(cursor->content) > -1))
		{
			join = NULL;
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
	int		j;
	char	*word;
	char	*help;

	if (*i != 0)
		*join = ft_strjoin_2(*join, extract_word_1(cursor->content, *i));
	j = *i;
	while (cursor && cursor->content[j] != is_special(cursor->content[j])
		&& cursor->content[j] != '=')
		j++;
	word = extract_word(cursor->content, i, j - *i);
	help = *join;
	if (!ft_get_env(env, &word[1]))
		*join = ft_strjoin(*join, "");
	else
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
<<<<<<< HEAD:expansion/expand.c
	s = content;
=======
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
>>>>>>> 58fc06fcd125f870e055373a2db9a0d82236ea53:expand.c
}
