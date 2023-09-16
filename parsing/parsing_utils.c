/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:26:52 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/16 23:44:11 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*detect_redir(t_elem *start, t_elem *end)
{
	t_redir			*redir;
	enum e_redir	type;
	char			*file_name;

	redir = NULL;
	type = NONE;
	file_name = "\0";
	if (!is_redir_exist(start, end))
		return (NULL);
	while (start && start != end)
	{
		if (start && (start->type == REDIR_IN || start->type == REDIR_ADD
				|| start->type == REDIR_APPEND || start->type == HER_DOC))
		{
			get_redir_type(start, &type, &file_name);
			add_back_redir(&redir, new_redir(type, file_name));
		}
		start = start->next;
	}
	return (redir);
}

void	get_redir_type(t_elem *start, enum e_redir *type, char **file_name)
{
	if (start->type == REDIR_IN)
		*type = INPUT;
	else if (start->type == REDIR_ADD)
		*type = ADD;
	else if (start->type == REDIR_APPEND)
		*type = APPEND;
	else if (start->type == HER_DOC)
		*type = HERDOC;
	while (start && start->type != WORD)
		start = start->next;
	if (start && start->type == WORD)
		*file_name = start->content;
}

t_redir	*detect_redir_final(t_elem *start)
{
	t_redir			*redir;
	enum e_redir	type;
	char			*file_name;

	if (!count_redir(start))
		return (NULL);
	redir = NULL;
	type = NONE;
	file_name = "\0";
	while (start)
	{
		if (start && (start->type == REDIR_IN || start->type == REDIR_ADD
				|| start->type == REDIR_APPEND || start->type == HER_DOC))
		{
			if (start->state == NORMAL)
			{
				get_redir_type(start, &type, &file_name);
				add_back_redir(&redir, new_redir(type, file_name));
				if (!start->next)
					break ;
			}
		}
		move_to_next_1(&start);
	}
	return (redir);
}

int	count_nodes(t_elem *start)
{
	int		count;

	count = 0;
	while (start)
	{
		count++;
		start = start->next;
	}
	return (count);
}

int	ft_strcmp_redir(char *str, t_redir *redir)
{
	t_redir		*c;

	c = redir;
	while (c)
	{
		if (str && !ft_strcmp(str, c->file_name))
			return (0);
		c = c->next;
	}
	return (1);
}
