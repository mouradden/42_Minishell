/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:00:10 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/21 22:36:24 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_normal_state(t_env *env, t_elem *cursor)
{
	char	*var;

	if (cursor && !ft_strcmp(cursor->content, "$?"))
		free_and_assign(cursor->content, ft_strdup(ft_itoa(g_exit_status)));
	else
	{
		if (cursor->content[1] >= '0' && cursor->content[1] <= '9')
			free_and_assign(cursor->content, ft_strdup(&cursor->content[2]));
		else if (cursor && !ft_get_env(env, &(cursor->content[1])))
		{
			var = ft_strdup("");
			free(cursor->content);
			cursor->content = var;
		}
		else
		{
			var = ft_get_env(env, &(cursor->content[1]));
			// free(cursor->content);
			cursor->content = remove_spaces(var);
		}
	}
}

void	expand_dquote_state(t_env *env, t_elem *cursor)
{
	char	*var;

	if (cursor && !ft_strcmp(cursor->content, "$?"))
		free_and_assign(cursor->content, ft_strdup(ft_itoa(g_exit_status)));
	else
	{
		if (cursor->content[1] >= '0' && cursor->content[1] <= '9')
			free_and_assign(cursor->content, ft_strdup(&cursor->content[2]));
		else if (cursor && !ft_get_env(env, &(cursor->content[1])))
			free_and_assign(cursor->content, ft_strdup(""));
		else
		{
			var = ft_get_env(env, &(cursor->content[1]));
			free(cursor->content);
			cursor->content = ft_strdup(var);
		}
	}
}
