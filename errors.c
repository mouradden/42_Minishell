/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:00:45 by mdenguir          #+#    #+#             */
/*   Updated: 2023/08/15 13:55:09 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_errors(t_env *env)
{
	if (!check_quotes(env))
	{
		printf("syntax error : unclosed quotes\n");
		env->exit_status = 258;
		return (0);
	}
	if (!check_syntax_pipes(env))
	{
		printf("syntax error : pipes \n");
		env->exit_status = 258;
		return (0);
	}
	if (!check_redir_syntax(env))
	{
		printf("syntax error : redirections \n");
		env->exit_status = 258;
		return (0);
	}
	return (1);
}

int	check_syntax_pipes(t_env *env)
{
	if (count_cmd(env->elem))
	{
		if (!check_before_pipe(env->elem))
			return (0);
		if (!check_consecutive_pipes(env->elem))
			return (0);
		if (!check_after_pipe(env->elem))
			return (0);
	}
	return (1);
}

int	check_redir_syntax(t_env *env)
{
	if (count_redir(env->elem))
	{
		if (!check_empty_redir(env->elem))
			return (0);
		if (!check_invalid_redir(env->elem))
			return (0);
		if (!invalid_consecutives_redir(env->elem))
			return (0);
	}
	return (1);
}

int	check_empty_redir(t_elem *elem)
{
	t_elem	*cursor;

	cursor = elem;
	while (cursor)
	{
		if (cursor && is_redir(cursor) && cursor->next)
		{
			if (cursor)
				cursor = cursor->next;
			while (cursor && cursor->type != WORD)
				cursor = cursor->next;
			if (cursor && cursor->type == WORD)
				return (1);
		}
		if (cursor)
			cursor = cursor->next;
	}
	return (0);
}

int	check_invalid_redir(t_elem *elem)
{
	t_elem	*cursor;

	cursor = elem;
	while (cursor)
	{
		if (cursor && cursor->next)
		{
			if (cursor->type == HER_DOC
				&& (cursor->next->type == REDIR_IN
					|| cursor->next->type == HER_DOC))
				return (0);
			if (cursor->type == REDIR_APPEND
				&& (cursor->next->type == REDIR_APPEND
					|| cursor->next->type == REDIR_ADD))
				return (0);
			if (cursor->type == REDIR_IN && cursor->next->type == REDIR_ADD)
				return (0);
			if (cursor->type == REDIR_ADD && cursor->next->type == REDIR_IN)
				return (0);
		}
		cursor = cursor->next;
	}
	return (1);
}

int	invalid_consecutives_redir(t_elem *elem)
{
	t_elem		*cursor;

	cursor = elem;
	while (cursor)
	{
		if (cursor && is_redir(cursor) && cursor->next)
		{
			if (cursor)
				cursor = cursor->next;
			while (cursor && !is_redir(cursor))
			{
				if (cursor->type == WORD)
					return (1);
				cursor = cursor->next;
			}
			if (cursor && is_redir(cursor))
				return (0);
		}
		cursor = cursor->next;
	}
	return (1);
}

int	is_redir(t_elem *elem)
{
	if (elem->type == REDIR_IN || elem->type == REDIR_ADD
		|| elem->type == REDIR_APPEND || elem->type == HER_DOC)
	{
		return (1);
	}
	return (0);
}

int	is_redir_exist(t_elem *start, t_elem *end)
{
	while (start && start != end)
	{
		if (is_redir(start))
			return (1);
		start = start->next;
	}
	return (0);
}
int	check_consecutive_pipes(t_elem *elem)
{
	t_elem		*cursor;

	cursor = elem;
	while (cursor)
	{
		if (cursor && cursor->next)
		{
			if (cursor->type == PIPE && cursor->next->type == PIPE)
				return (0);
		}
		cursor = cursor->next;
	}
	cursor = elem;
	while (cursor)
	{
		if (cursor->type == PIPE && cursor->next
			&& cursor->next->type == WHITE_SPACE)
		{
			cursor = cursor->next;
			while (cursor && cursor->type == WHITE_SPACE)
				cursor = cursor->next;
			if (cursor && cursor->type == PIPE)
				return (0);
		}
		if (cursor)
			cursor = cursor->next;
	}
	return (1);
}

int	check_before_pipe(t_elem *elem)
{
	t_elem		*cursor;

	cursor = elem;
	while (cursor && cursor->type == WHITE_SPACE)
		cursor = cursor->next;
	if (cursor && cursor->type == PIPE)
		return (0);
	cursor = elem;
	while (cursor && cursor->type != PIPE)
	{
		if (cursor->type == WORD)
			return (1);
		cursor = cursor->next;
	}
	return (0);
}

int	check_after_pipe(t_elem *elem)
{
	t_elem		*cursor;
	int			n;

	cursor = elem;
	n = count_cmd(cursor);
	while (n && cursor)
	{
		while (cursor && cursor->type != PIPE)
			cursor = cursor->next;
		if (cursor && cursor->type != PIPE)
			return (1);
		if (cursor)
			cursor = cursor->next;
		n--;
	}
	if (cursor)
	{
		while (cursor)
		{
			if (cursor->type == WORD)
				return (1);
			cursor = cursor->next;
		}
	}
	return (0);
}

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

int	count_redir(t_elem *list)
{
	int		count;
	t_elem	*cursor;

	count = 0;
	cursor = list;
	while (cursor)
	{
		if (is_redir(cursor))
			count++;
		cursor = cursor->next;
	}
	return (count);
}
