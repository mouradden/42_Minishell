/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:18:52 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/26 18:35:29 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(t_envp **envp, char *title)
{
	if (check_duplicate(envp, title))
	{
		remove_node(envp, title);
	}
	g_exit_status = 0;
}

void	remove_node(t_envp **envp, char *var)
{
	t_envp	*cursor;
	t_envp	*node_temp;

	remove_head(envp, var);
	if (*envp)
	{
		cursor = *envp;
		while (cursor->next)
		{
			if (cursor->next->title && var
				&& !ft_strcmp(cursor->next->title, var))
			{
				node_temp = cursor->next->next;
				free(cursor->next->title);
				free (cursor->next->equal);
				free(cursor->next->content);
				free(cursor->next);
				cursor->next = node_temp;
				break ;
			}
			cursor = cursor->next;
		}
	}
}

void	remove_head(t_envp **envp, char *var)
{
	t_envp	*node_temp;

	if (*envp && (*envp)->title && var && !ft_strcmp((*envp)->title, var))
	{
		node_temp = (*envp)->next;
		free((*envp)->title);
		free((*envp)->equal);
		free((*envp)->content);
		free((*envp));
		*envp = node_temp;
	}
}
