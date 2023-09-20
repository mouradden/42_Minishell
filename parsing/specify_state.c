/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specify_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 10:13:59 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/20 21:55:09 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	isolate_quotes(t_elem **elem)
{
	t_elem		*cursor;

	cursor = *elem;
	while (cursor)
	{
		if (cursor && cursor->type == S_QUOTE)
		{
			cursor = cursor->next;
			while (cursor && cursor->type != S_QUOTE)
			{
				cursor->state = IN_QUOTE;
				cursor = cursor->next;
			}
		}
		if (cursor && cursor->type == D_QUOTE)
		{
			cursor = cursor->next;
			while (cursor && cursor->type != D_QUOTE)
			{
				cursor->state = IN_DQUOTE;
				cursor = cursor->next;
			}
		}
		to_next(&cursor);
	}
}

void	to_next(t_elem **cursor)
{
	if (*cursor)
		*cursor = (*cursor)->next;
}
