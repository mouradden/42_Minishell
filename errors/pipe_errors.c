/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:24:48 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/22 22:23:22 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_consecutive_pipes(t_elem *elem)
{
	t_elem		*cursor;

	cursor = elem;
	if (!check_2_consecutives(cursor))
		return (0);
	cursor = elem;
	if (!check_separated_consecutives(cursor))
		return (0);
	return (1);
}

int	check_2_consecutives(t_elem *cursor)
{
	while (cursor)
	{
		if (cursor && cursor->next)
		{
			if (cursor->type == PIPE && cursor->next->type == PIPE
			&& cursor->state == NORMAL && cursor->next->state == NORMAL)
				return (0);
		}
		cursor = cursor->next;
	}
	return (1);
}

int	check_separated_consecutives(t_elem *cursor)
{
	while (cursor)
	{
		if (cursor->type == PIPE && cursor->state == NORMAL
		&& cursor->next && cursor->next->type == WHITE_SPACE)
		{
			cursor = cursor->next;
			while (cursor && cursor->type == WHITE_SPACE)
				cursor = cursor->next;
			if (cursor && cursor->type == PIPE && cursor->state == NORMAL)
				return (0);
		}
		if (cursor)
			cursor = cursor->next;
	}
	return (1);
}

int	check_before_pipe(t_elem *elem)
{
	t_elem		*cursor;

	cursor = elem;
	while (cursor && cursor->type == WHITE_SPACE)
		cursor = cursor->next;
	if (cursor && cursor->type == PIPE)
		return (0);
	cursor = elem;
	while (cursor && cursor->type != PIPE)
	{
		if (cursor->type == WORD)
			return (1);
		cursor = cursor->next;
	}
	return (0);
}

int	check_after_pipe(t_elem *elem)
{
	t_elem		*cursor;
	int			n;

	cursor = elem;
	n = count_cmd(&cursor);
	while (n && cursor)
	{
		while (cursor && cursor->type != PIPE)
			cursor = cursor->next;
		if (cursor && cursor->type != PIPE)
			return (1);
		if (cursor)
			cursor = cursor->next;
		n--;
	}
	if (cursor)
	{
		while (cursor)
		{
			if (cursor->type == WORD)
				return (1);
			cursor = cursor->next;
		}
	}
	return (0);
}
