/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_errors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:25:02 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/23 10:22:09 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir(t_elem *elem)
{
	if (elem->type == REDIR_IN || elem->type == REDIR_ADD
		|| elem->type == REDIR_APPEND || elem->type == HER_DOC)
	{
		return (1);
	}
	return (0);
}

int	is_redir_exist(t_elem *start, t_elem *end)
{
	while (start && start != end)
	{
		if (is_redir(start))
			return (1);
		start = start->next;
	}
	return (0);
}

int	count_redir(t_elem *list)
{
	int		count;
	t_elem	*cursor;

	count = 0;
	cursor = list;
	while (cursor)
	{
		if (is_redir(cursor) && cursor->state == NORMAL)
			count++;
		cursor = cursor->next;
	}
	return (count);
}
