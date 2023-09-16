/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 20:48:29 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/16 10:05:49 by mdenguir         ###   ########.fr       */
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
		cmd_line = malloc((count_before_pipe(start) + 1) * sizeof(char *));
		i = 0;
		get_redirs(cursor, start, &redir);
		while (start && start != cursor)
			extract_args(&start, &cmd_line, &redir, &i);
		cmd_line[i] = 0;
		add_back_cmd(cmd, cmd_line, redir);
		if (cursor && start)
		{
			cursor = cursor->next;
			start = start->next;
		}
	}
}

void	move_to_next(t_elem *start, t_elem *cursor)
{
	if (cursor && start)
	{
		cursor = cursor->next;
		start = start->next;
	}
}

void	get_redirs(t_elem *cursor, t_elem *start, t_redir **redir)
{
	if (!cursor)
		*redir = detect_redir_final(start);
	else if (cursor->type == PIPE)
		*redir = detect_redir(start, cursor);
}

void	extract_args(t_elem **start, char ***cmd_line, t_redir **redir, int *i)
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
