/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:45:55 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/16 22:52:03 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_back_cmd(t_cmd **cmd_list, char **line, t_redir *redir)
{
	t_cmd		*cursor;
	t_cmd		*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return ;
	new->cmd_line = line;
	new->redir = redir;
	new->next = NULL;
	cursor = *cmd_list;
	if (!cursor)
	{
		*cmd_list = new;
	}
	else
	{
		cursor = *cmd_list;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = new;
	}
}

int	count_delimter_pipe(t_elem *list)
{
	t_elem	*cursor;
	int		count;

	cursor = list;
	count = 0;
	while (cursor)
	{
		if (cursor->type == PIPE && cursor->state == NORMAL)
			count++;
		cursor = cursor->next;
	}
	return (count);
}

int	count_before_pipe(t_elem *list)
{
	int		count;
	t_elem	*cursor;

	count = 0;
	cursor = list;
	while (cursor)
	{
		if (cursor->type == PIPE && cursor->state == NORMAL)
			break ;
		else
		{
			count++;
			cursor = cursor->next;
		}
	}
	return (count);
}

int	count_cmd(t_elem **list)
{
	int		count;
	t_elem	*cursor;

	count = 0;
	cursor = *list;
	while (cursor)
	{
		if (cursor->type == PIPE)
			count++;
		cursor = cursor->next;
	}
	return (count);
}
