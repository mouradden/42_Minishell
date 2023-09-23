/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 10:43:09 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/23 22:20:01 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_command(t_elem **elem, char *input)
{
	int				i;

	i = 0;
	while (input[i] && input[i] != '\n')
	{
		if (input[i] && is_space(input[i]))
			add_back(elem, new_elem(input, &i, 1, WHITE_SPACE));
		else if (input[i] && input[i] == '$')
			get_var(elem, input, &i);
		else if (input[i] && !is_special(input[i]))
			get_word(elem, input, &i);
		else if (input[i] && (input[i] == '|'
				|| input[i] == '\'' || input[i] == '"'))
			get_quotes_or_pipe(elem, input, &i);
		else if (input[i] && input[i] == '>' && input[i + 1] == '>')
			add_back(elem, new_elem(input, &i, 2, REDIR_APPEND));
		else if (input[i] && input[i] == '>')
			add_back(elem, new_elem(input, &i, 1, REDIR_ADD));
		else if (input[i] && input[i] == '<' && input[i + 1] == '<')
			add_back(elem, new_elem(input, &i, 2, HER_DOC));
		else if (input[i] && input[i] == '<')
			add_back(elem, new_elem(input, &i, 1, REDIR_IN));
	}
	isolate_quotes(elem);
}

void	get_quotes_or_pipe(t_elem **elem, char *input, int *i)
{
	if (input[*i] && input[*i] == '\'')
		add_back(elem, new_elem(input, i, 1, S_QUOTE));
	else if (input[*i] && input[*i] == '"')
		add_back(elem, new_elem(input, i, 1, D_QUOTE));
	else if (input[*i] && input[*i] == '|')
		add_back(elem, new_elem(input, i, 1, PIPE));
}

void	get_var(t_elem **elem, char *input, int *i)
{
	int		j;

	j = *i;
	if (input[*i] == '$' && !input[*i + 1])
		add_back(elem, new_elem(input, i, 1, WORD));
	else if (input[*i] == '$' && input[*i + 1] && input[*i + 1] == '?')
		add_back(elem, new_elem(input, i, 2, WORD));
	else
	{
		while (input[j])
		{
			j++;
			if (input[j] && (is_special(input[j]) || input[j] == '$'))
				break ;
		}
	}
	add_back(elem, new_elem(input, i, j - *i, VAR));
}

void	get_word(t_elem **elem, char *input, int *i)
{
	int		j;
	int		len;
	t_tmp	tmp;

	j = *i;
	len = 0;
	while (input[j] && !is_special(input[j]))
	{
		len++;
		j++;
	}
	if (input[j - 1] && input[j - 1] == '='
		&& (input[j] == '\'' || input[j] == '"'))
	{
		tmp.j = j;
		tmp.len = len;
		parse_equal(elem, input, i, tmp);
	}
	else
		add_back(elem, new_elem(input, i, len, WORD));
}

void	parse_equal(t_elem **elem, char *input, int *i, t_tmp tmp)
{
	int		j;
	int		s_q;
	int		d_q;

	j = tmp.j - 1;
	s_q = 0;
	d_q = 0;
	if (input[j] == '=' && input[j + 1]
		&& (input[j + 1] == '\'' || input[j + 1] == '"'))
	{
		count_quotes(input[j + 1], &d_q, &s_q);
		j += 2;
		while (input[j] && input[j + 1])
		{
			count_quotes(input[j], &d_q, &s_q);
			if ((input[j] == '"' && input[j + 1] == ' ')
				|| (input[j] == '\'' && input[j + 1] == ' ')
				|| (input[j] == ' ' && ((s_q % 2 == 0 && s_q)
						|| (d_q % 2 == 0 && d_q))))
				break ;
			tmp.len++;
			j++;
		}
		add_back(elem, new_elem(input, i, tmp.len + 2, WORD));
	}
}
