/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:24:57 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/14 20:26:00 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes(t_env *env)
{
	t_elem		*cursor;
	int			count_single;
	int			count_double;

	cursor = env->elem;
	count_double = 0;
	count_single = 0;
	while (cursor)
	{
		if (cursor->type == S_QUOTE && cursor->state == NORMAL)
			count_single++;
		if (cursor->type == D_QUOTE && cursor->state == NORMAL)
			count_double++;
		cursor = cursor->next;
	}
	if (count_single % 2 || count_double % 2)
		return (0);
	return (1);
}
