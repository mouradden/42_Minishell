/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:15:01 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/23 15:29:28 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_empty_redir(t_elem *elem)
{
	t_elem	*cursor;

	cursor = elem;
	while (cursor)
	{
		if (cursor && is_redir(cursor) && cursor->state == NORMAL && cursor->next)
		{
			if (cursor)
				cursor = cursor->next;
			while (cursor && cursor->type != WORD)
				cursor = cursor->next;
			while (cursor && is_redir(cursor))
				cursor = cursor->next;
			
		}
		while (cursor)
		{
			if (cursor && is_redir(cursor) && !cursor->next)
				return (0);
			cursor = cursor->next;
		}
		if (cursor)
				cursor = cursor->next;
	}
	return (1);
}

int	check_invalid_redir(t_elem *elem)
{
	t_elem	*cursor;

	cursor = elem;
	while (cursor)
	{
		if (cursor && cursor->next)
		{
			if (cursor->type == HER_DOC
				&& (cursor->next->type == REDIR_IN
					|| cursor->next->type == HER_DOC))
				return (0);
			if (cursor->type == REDIR_APPEND
				&& (cursor->next->type == REDIR_APPEND
					|| cursor->next->type == REDIR_ADD))
				return (0);
			if (cursor->type == REDIR_IN && cursor->next->type == REDIR_ADD)
				return (0);
			if (cursor->type == REDIR_ADD && cursor->next->type == REDIR_IN)
				return (0);
		}
		cursor = cursor->next;
	}
	return (1);
}

int	invalid_consecutives_redir(t_elem *elem)
{
	t_elem		*cursor;

	cursor = elem;
	while (cursor)
	{
		if (cursor && is_redir(cursor) && cursor->state == NORMAL && cursor->next)
		{
			if (cursor)
			{
				cursor = cursor->next;
				while (cursor && cursor->type == WHITE_SPACE)
					cursor = cursor->next;
			}
			while (cursor && !is_redir(cursor))
			{
				if (cursor->type == WORD)
					return (1);
				cursor = cursor->next;
			}
			if (cursor && is_redir(cursor) && cursor->state == NORMAL)
				return (0);
		}
		cursor = cursor->next;
	}
	return (1);
}
