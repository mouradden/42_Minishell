/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:26:52 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/15 17:52:00 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_line(t_cmd **cmd, t_elem **list)
{
	t_elem		*start;
	t_elem		*cursor;
	char		**cmd_line;
	int			i;
	t_redir		*redir;

	start = *list;
	cursor = *list;
	redir = NULL;
	while (cursor)
	{
		while (cursor && cursor->type != PIPE)
			cursor = cursor->next;
		cmd_line = malloc(count_before_pipe(start) * sizeof(char *));
		i = 0;
		get_redirs(cursor, start, &redir);
		while (start && start != cursor)
			iterate_and_extract_args(&start, &cmd_line, &redir, &i);
		cmd_line[i] = 0;
		add_back_cmd(cmd, cmd_line, redir);
		if (cursor && start)
		{
			cursor = cursor->next;
			start = start->next;
		}
	}
}

void	get_redirs(t_elem *cursor, t_elem *start, t_redir **redir)
{
	if (!cursor)
		*redir = detect_redir_final(start);
	else if (cursor->type == PIPE)
		*redir = detect_redir(start, cursor);
}
void	iterate_and_extract_args(t_elem **start, char ***cmd_line, t_redir **redir, int *i)
{
	if ((*start)->content && ft_strcmp_redir((*start)->content, *redir)
		&& (*start)->type != REDIR_IN && (*start)->type != REDIR_ADD
		&& (*start)->type != REDIR_APPEND && (*start)->type != HER_DOC)
		fill_cmd_and_args(*start, cmd_line, i);
	(*start) = (*start)->next;
}
void	fill_cmd_and_args(t_elem *start, char ***cmd_line, int *i)
{
	char	**splited;
	int		j;

	if (is_contains(start->content, ' ') == -1)
	{
		(*cmd_line)[*i] = ft_strdup(start->content);
		(*i)++;
	}
	else if (start->type == VAR && is_contains(start->content, ' ') > -1)
	{
		splited = ft_split(start->content, ' ');
		j = 0;
		while (splited[j])
		{
			(*cmd_line)[*i] = ft_strdup(splited[j]);
			(*i)++;
			j++;
		}
		free_double(splited);
	}
	else
	{
		(*cmd_line)[*i] = ft_strdup(start->content);
		(*i)++;
	}
}

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
	// redir = malloc(sizeof(t_redir));
	// if (!redir)
	// 	return (NULL);
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
