/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:41:20 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/11 22:25:45 by mdenguir         ###   ########.fr       */
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
			if (cursor->content && cursor->equal && !ft_strcmp(cursor->equal, "="))
			{
				ft_putchar_fd('=', 1);
				ft_putstr_fd(cursor->content, 1);
			}
			ft_putchar_fd('\n', 1);
		}
		cursor = cursor->next;
	}
}

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

int	count_nodes_env(t_envp *envp)
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
	// list = malloc(sizeof(t_envp));
	// if (!list)
	// 	return (NULL);
	list = NULL;
	while (envp[i])
	{
		split_env(&list, envp[i]);
		i++;
	}
	return (list);
}

int	check_title(char *title)
{
	int	i;

	i = 0;
	if (title[i])
	{
		if (title[i] == '_' || (title[i] >= 'a' && title[i] <= 'z') || (title[i] >= 'A' && title[i] <= 'Z'))
			return (1);
	}
	return (0);
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
		// if(title)
			node->title = title;
		// if(content)
			node->content = content;
		// if(equal)
			node->equal = equal;
		node->next = NULL;
		add_back_env(list, node);
		// if(title)
		// 	free(title);
		// if(content)
		// 	free(content);
		// if(equal)
		// 	free(equal);
	}
	
}

void	split_env(t_envp **list, char *envp)
{
	char	*title;
	char	*content;
	char	*equal;
	int		i;
	int		len;
	int		j;

	i = 0;
	while (envp[i])
	{
		j = i;
		// len = 0;
		while (envp[j] && envp[j] != '=')
		{
			// len++;
			j++;
		}
		title = extract_word(envp, &i, j - i);
		if (!check_title(title))
		{
			ft_putstr_fd("export: `", 1);
			ft_putstr_fd(envp, 1);
			ft_putstr_fd("`: not a valid identifier\n", 1);
			break ;
		}
		if (envp[i] == '=')
			equal = extract_word(envp, &i, 1);
		len = 0;
		if (envp[i] == '"' || envp[i] == '"')
			i++;
		j = i;
		while (envp[j] && envp[j] != '"' && envp[j] != '\'')
		{
			// len++;
			j++;
		}
		content = extract_word(envp, &i, j - i);
		if (envp[i] == '"' || envp[i] == '"')
			i++;
	}
	// printf("-->%p || %p || %p\n", title, content, equal);
	add_to_env(list, title, content, equal);
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
