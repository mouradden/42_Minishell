/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:40:44 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/16 12:22:52 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_env *env)
{
	free_elem(env);
	free_cmd(env);
}

void	free_elem(t_env *env)
{
	t_elem	*node;
	t_elem	*cursor;

	cursor = (env)->elem;
	while (cursor)
	{
		node = cursor->next;
		free(cursor->content);
		free(cursor);
		cursor = node;
	}
}

void	free_redir(t_redir *redir)
{
	t_redir	*cursor;
	t_redir	*tmp;

	cursor = redir;
	while (cursor)
	{
		tmp = cursor->next;
		free(cursor);
		cursor = tmp;
	}
}

void	free_cmd(t_env *env)
{
	t_cmd		*cursor;
	t_cmd		*tmp;

	cursor = env->cmd;
	while (cursor)
	{
		tmp = cursor->next;
		free_double(cursor->cmd_line);
		if (cursor->redir)
			free_redir(cursor->redir);
		free(cursor);
		cursor = tmp;
	}
}

void	free_envp(t_env *env)
{
	t_envp		*cursor;
	t_envp		*tmp;

	cursor = (env)->envp;
	while (cursor)
	{
		tmp = cursor->next;
		free(cursor->title);
		free(cursor->content);
		free(cursor->equal);
		cursor = tmp;
	}
}
