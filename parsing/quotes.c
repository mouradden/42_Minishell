/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:02:22 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/19 15:02:27 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_rid_of_quotes(t_elem **list)
{
	t_elem	*cursor;

	if (!(*list))
		return ;
	if (!trim_front_quotes(list))
		return ;
	if (*list)
	{
		cursor = *list;
		trim_quotes_btw(cursor);
	}
}

int	trim_front_quotes(t_elem **list)
{
	t_elem	*temp;

	while (((*list)->type == S_QUOTE || (*list)->type == D_QUOTE)
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

void	trim_quotes_btw(t_elem *cursor)
{
	t_elem	*temp;

	while (cursor->next)
	{
		if ((cursor->next->type == S_QUOTE || cursor->next->type == D_QUOTE)
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

void	count_quotes(char c, int *d_q, int *s_q)
{
	if (c == '\'')
		(*s_q)++;
	if (c == '"')
		(*d_q)++;
}
