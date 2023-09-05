/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 22:53:44 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/05 15:57:07 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	**env_2_d(t_envp *envp)
{
	t_envp	*cursor;
	char	**res;
	int		i;
	int		index;

	cursor = envp;
	i = 0;
	index = 0;
	res = malloc(count_nodes_env(envp) * sizeof(char *) + 1);
	while (cursor)
	{
		res[i] = malloc(count_content_length(cursor) + 2);
		res[i] = ft_strcat(cursor->title, "=");
		res[i] = ft_strcat(res[i], cursor->content);
		i++;
		cursor = cursor->next;
	}
	return (res);
}

int		count_nodes_env(t_envp *envp)
{
	t_envp	*cursor;
	int		count;

	count = 0;
	cursor = envp;
	while (cursor)
	{
		count++;
		cursor = cursor->next;
	}
	return (count);
}

int	count_content_length(t_envp *node)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (node->title[i])
	{
		count++;
		i++;
	}
	i = 0;
	while (node->content[i])
	{
		count++;
		i++;
	}
	return (count);
}

t_envp	*copy_env(char **envp)
{
	t_envp	*list;
	int		i;

	i = 0;
	list = malloc(sizeof(t_envp));
	if (!list)
		return (NULL);
	list = NULL;
	while (envp[i])
	{
		split_env(&list, envp[i]);
		i++;
	}
	return (list);
}

void	split_env(t_envp **list, char *envp)
{
	t_envp	*node;
	int		i;
	int		len;
	int		j;

	i = 0;
	node = malloc(sizeof(t_envp));
	if (!node)
		return ;
	while (envp[i])
	{
		j = i;
		len = 0;
		while (envp[j] && envp[j] != '=')
		{
			len++;
			j++;
		}
		node->title = extract_word(envp, &i, len);
		if (envp[i] == '=')
			node->equal = extract_word(envp, &i, 1);
		len = 0;
		if (envp[i] == '"' || envp[i] == '"')
			i++;
		j = i;
		while (envp[j] && envp[j] != '"' && envp[j] != '\'')
		{
			len++;
			j++;
		}
		node->content = extract_word(envp, &i, len);
		
		if (envp[i] == '"' || envp[i] == '"')
			i++;
		node->next = NULL;
	}
	if (check_duplicate(list, node->title))
	{
		update_node(*list, node->title, node->content);
	}
	else
	{
		add_back_env(list, node);
	}
}

void	add_back_env(t_envp **head, t_envp *new)
{
	t_envp		*cursor;

	if (*head == NULL)
	{
		*head = new;
	}
	else
	{
		cursor = *head;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = new;
	}
}

void	ft_env(t_envp **envp)
{
	t_envp	*cursor;

	cursor = *envp;
	while (cursor)
	{
		if (cursor->title)
		{
			ft_putstr_fd(cursor->title, 1);
			if (cursor->equal && !ft_strcmp(cursor->equal, "="))
			{
				ft_putchar_fd('=', 1);
				ft_putstr_fd(cursor->content, 1);
				
			}
			ft_putchar_fd('\n', 1);
		}
		
		cursor = cursor->next;
	}
}
