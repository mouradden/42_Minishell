/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:02:29 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/15 17:02:30 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_rid_of_spaces(t_elem **list)
{
	t_elem	*cursor;

	if (!(*list))
		return ;
	if (!trim_front_spaces(list))
		return ;
	if (*list)
	{
		cursor = *list;
		trim_spaces_btw(cursor);
	}
}

int	trim_front_spaces(t_elem **list)
{
	t_elem	*temp;

	while ((*list)->type == WHITE_SPACE
		&& (*list)->state == NORMAL)
	{
		temp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = temp;
		if (!(*list))
			return (0);
	}
	return (1);
}

void	trim_spaces_btw(t_elem *cursor)
{
	t_elem	*temp;

	while (cursor->next)
	{
		if (cursor->next->type == WHITE_SPACE
			&& cursor->next->state == NORMAL)
		{
			temp = cursor->next;
			cursor->next = cursor->next->next;
			free(temp->content);
			free(temp);
		}
		else
			cursor = cursor->next;
	}
}
