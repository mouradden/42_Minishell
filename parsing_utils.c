/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:26:52 by mdenguir          #+#    #+#             */
/*   Updated: 2023/08/16 10:36:19 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_delimter_pipe(t_elem *list)
{
	t_elem		*cursor;
	int			count;

	cursor = list;
	count = 0;
	while (cursor)
	{
		if (cursor->type == PIPE)
			count++;
		cursor = cursor->next;
	}
	return (count);
}

int	count_before_pipe(t_elem *list)
{
	int		count;
	t_elem	*cursor;

	count = 0;
	cursor = list;
	while (cursor && cursor->type != PIPE)
	{
		count++;
		cursor = cursor->next;
	}
	return (count);
}

void	add_back_cmd(t_cmd **cmd_list, char **line, t_redir *redir)
{
	t_cmd		*cursor;
	t_cmd		*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return ;
	new->redir = malloc(sizeof(t_redir));
	new->cmd_line = line;
	new->redir = redir;
	new->next = NULL;
	if (!(*cmd_list))
	{
		*cmd_list = new;
	}
	else
	{
		cursor = *cmd_list;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = new;
	}
}

int	count_cmd(t_elem *list)
{
	int		count;
	t_elem	*cursor;

	count = 0;
	cursor = list;
	while (cursor)
	{
		if (cursor->type == PIPE)
			count++;
		cursor = cursor->next;
	}
	return (count);
}

void	get_rid_of_spaces(t_elem **list)
{
	t_elem	*cursor;
	t_elem	*temp;

	cursor = *list;
	if (!(*list))
		return ;
	cursor = *list;
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

void	get_rid_of_quotes(t_elem **list)
{
	t_elem	*cursor;
	t_elem	*temp;

	cursor = *list;
	if (!(*list))
		return ;
	cursor = *list;
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

t_cmd	*split_line(t_elem *list)
{
	t_cmd		*cmd;
	t_elem		*start;
	t_elem		*cursor;
	char		**cmd_line;
	int			i;
	int			count;
	t_redir		*redir;

	start = list;
	cursor = list;
	cmd = NULL;
	count = count_cmd(list) + 1;
	redir = NULL;
	while (cursor)
	{
		while (cursor && cursor->type != PIPE)
			cursor = cursor->next;
		cmd_line = malloc(count_before_pipe(start) * sizeof(char *) + 1);
		i = 0;
		if (!cursor)
			redir = detect_redir_final(start);
		else if (cursor->type == PIPE)
			redir = detect_redir(start, cursor);
		while (start && start != cursor)
		{
			if (ft_strcmp_redir(start->content, redir)
				&& start->type != REDIR_IN && start->type != REDIR_ADD
				&& start->type != REDIR_APPEND && start->type != HER_DOC)
			{
				cmd_line[i] = start->content;
				i++;
			}
				start = start->next;
		}
		cmd_line[i] = 0;
		add_back_cmd(&cmd, cmd_line, redir);
		if (cursor && start)
		{
			cursor = cursor->next;
			start = start->next;
		}
	}
	return (cmd);
}

t_redir	*detect_redir(t_elem *start, t_elem *end)
{
	t_redir			*redir;
	enum e_redir	type;
	char			*file_name;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
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
			if (start->type == REDIR_IN)
				type = INPUT;
			else if (start->type == REDIR_ADD)
				type = ADD;
			else if (start->type == REDIR_APPEND)
				type = APPEND;
			else if (start->type == HER_DOC)
				type = HERDOC;
			while (start && start->type != WORD)
				start = start->next;
			if (start && start->type == WORD)
				file_name = start->content;
			add_back_redir(&redir, new_redir(type, file_name));
		}
		start = start->next;
	}
	return (redir);
}

t_redir	*detect_redir_final(t_elem *start)
{
	t_redir			*redir;
	enum e_redir	type;
	char			*file_name;

	if (!count_redir(start))
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir = NULL;
	type = NONE;
	file_name = "\0";
	while (start)
	{
		if (start && (start->type == REDIR_IN || start->type == REDIR_ADD
				|| start->type == REDIR_APPEND || start->type == HER_DOC))
		{
			if (start->type == REDIR_IN)
				type = INPUT;
			else if (start->type == REDIR_ADD)
				type = ADD;
			else if (start->type == REDIR_APPEND)
				type = APPEND;
			else if (start->type == HER_DOC)
				type = HERDOC;
			while (start && start->type != WORD)
				start = start->next;
			if (start && start->type == WORD)
				file_name = start->content;
			add_back_redir(&redir, new_redir(type, file_name));
			if (!start->next)
				break ;
		}
		if (start)
			start = start->next;
	}
	return (redir);
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

t_redir	*new_redir(enum e_redir	type, char *file_name)
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

void	free_redir(t_redir *redir)
{
	t_redir		*cursor;

	while (redir)
	{
		cursor = redir->next;
		free(redir);
		redir = cursor;
	}
}

int	ft_strcmp_redir(char *str, t_redir *redir)
{
	t_redir		*c;

	c = redir;
	while (c)
	{
		if (!ft_strcmp(str, c->file_name))
			return (0);
		c = c->next;
	}
	return (1);
}
