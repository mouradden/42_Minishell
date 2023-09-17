/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:28:49 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/17 14:55:47 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_double(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_special(int c)
{
	return (c == ' ' || c == '\t' || c == '<' || c == '>'
		|| c == '\n' || c == '|' || c == '\'' || c == '"');
}

void	move_to_next(t_elem *start, t_elem *cursor)
{
	if (cursor && start)
	{
		cursor = cursor->next;
		start = start->next;
	}
}

void	move_to_next_1(t_elem **start)
{
	if (*start)
		*start = (*start)->next;
}
