/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:06:27 by mdenguir          #+#    #+#             */
/*   Updated: 2023/08/18 20:53:12 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void export(t_envp **envp, char *var)
{
	printf("-->%s\n", var);
	split_env(envp, var);
}

int check_duplicate(t_envp **envp, char *var)
{
	t_envp	*cursor;

	cursor = envp;
	while (cursor)
	{
		if (!ft_strcmp(cursor->title, var))
			return (1);
		cursor = cursor->next;
	}
	return (0);
}

void	update_node(t_envp *envp, char *var_title, char *var_content)
{
	t_envp	*cursor;

	cursor = envp;
	while (cursor)
	{
		if (!ft_strcmp(cursor->title, var_title))
		{
			free(cursor->content);
			cursor->content = var_content;
			break ;
		}
		cursor = cursor->next;
	}
}

void	remove_node(t_envp *envp, char *var)
{
	t_envp	*cursor;
	t_envp	*node_temp;

	cursor = envp;
	while (cursor->next)
	{
		if (!ft_strcmp(cursor->title, var))
		{
			node_temp = cursor->next;
			free(cursor->title);
			free(cursor->content);
			free(cursor);
			cursor = node_temp;
			break ;
		}
		cursor = cursor->next;
	}
}
