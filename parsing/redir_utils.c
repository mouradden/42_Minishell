/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:47:38 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/15 16:47:45 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*new_redir(enum e_redir type, char *file_name)
{
	t_redir		*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = type;
	new->file_name = file_name;
	new->next = NULL;
	return (new);
}

void	add_back_redir(t_redir **redir, t_redir *new)
{
	t_redir		*cursor;

	if (*redir == NULL)
		*redir = new;
	else
	{
		cursor = *redir;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = new;
	}
}
