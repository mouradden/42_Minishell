/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:18:52 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/20 22:21:41 by mdenguir         ###   ########.fr       */
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

	cursor = *envp;
	while (cursor->next)
	{
		if (cursor->next->title && var && !ft_strcmp(cursor->next->title, var))
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
