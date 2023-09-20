/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:41:20 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/20 22:21:13 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_envp **envp)
{
	t_envp	*cursor;

	cursor = *envp;
	while (cursor)
	{
		if (cursor->title)
		{
			ft_putstr_fd(cursor->title, 1);
			if (cursor->content && cursor->equal
				&& !ft_strcmp(cursor->equal, "="))
			{
				ft_putchar_fd('=', 1);
				ft_putstr_fd(cursor->content, 1);
			}
			ft_putchar_fd('\n', 1);
		}
		cursor = cursor->next;
	}
	g_exit_status = 0;
}

t_envp	*copy_env(char **envp)
{
	t_envp	*list;
	int		i;

	i = 0;
	list = NULL;
	while (envp[i])
	{
		split_env(&list, envp[i]);
		i++;
	}
	return (list);
}

void	add_to_env(t_envp **list, char *title, char *content, char *equal)
{
	t_envp	*node;

	if (check_title(title) && check_duplicate(list, title))
	{
		update_node(list, title, content);
		free(title);
		free(equal);
	}
	else if (check_title(title) && !check_duplicate(list, title))
	{
		node = malloc(sizeof(t_envp));
		if (!node)
			return ;
		node->title = title;
		node->content = content;
		node->equal = equal;
		node->next = NULL;
		add_back_env(list, node);
	}
}

void	split_env(t_envp **list, char *envp)
{
	char	*title;
	char	*content;
	char	*equal;
	int		i;

	i = 0;
	title = NULL;
	content = NULL;
	equal = NULL;
	parse_envp_line(envp, &title, &content, &equal);
	add_to_env(list, title, content, equal);
}

void	parse_envp_line(char *envp, char **tit, char **con, char **eq)
{
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		j = i;
		while (envp[j] && envp[j] != '=')
			j++;
		*tit = extract_word(envp, &i, j - i);
		if (check_identifier(*tit, envp))
			break ;
		if (envp[i] == '=')
			*eq = extract_word(envp, &i, 1);
		if (envp[i] == '"' || envp[i] == '"')
			i++;
		j = i;
		while (envp[j] && envp[j] != '"' && envp[j] != '\'')
			j++;
		*con = extract_word(envp, &i, j - i);
		if (envp[i] == '"' || envp[i] == '"')
			i++;
	}
}
