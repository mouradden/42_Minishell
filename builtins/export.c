/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:06:27 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/05 17:01:12 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void export(t_envp **envp, char **var)
{
	int		i;
	int		j;
	char	**splitted_var;

	i = 0;
	
	if (!var[1])
		display_export(envp);
	else
	{
		i = 1;
		while (var[i])
		{
			if ((is_contains(var[i], '=') > -1) && is_contains_before_equal(var[i], ' '))
			{
				splitted_var = ft_split(var[i], ' ');
				j = 0;
				while (splitted_var[j])
				{
					split_env(envp, splitted_var[j]);
					j++;
				}
				
			}
			else
				split_env(envp, var[i]);
			i++;
		}
	}
}

int	is_contains_before_equal(char *str, int c)
{
	int		i;

	i = 0;
	while (str[i] != '=')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_contains(char *str, int c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	display_export(t_envp **envp)
{
	t_envp		*cursor;

	cursor = *envp;
	while (cursor)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(cursor->title, 1);
		if (cursor->equal)
		{
			ft_putchar_fd('=', 1);
			ft_putchar_fd('"', 1);
			if (cursor->content)
				ft_putstr_fd(cursor->content, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		cursor = cursor->next;
	}
}

int check_duplicate(t_envp **envp, char *var)
{
	t_envp	*cursor;

	cursor = *envp;
	while (cursor)
	{
		if (cursor->title && var && !ft_strcmp(cursor->title, var))
			return (1);
		cursor = cursor->next;
	}
	return (0);
}

void	update_node(t_envp *envp, char *var_title, char *var_content)
{
	t_envp	*cursor;

	cursor = envp;
	while (cursor)
	{
		if (cursor->title && var_title && !ft_strcmp(cursor->title, var_title))
		{
			free(cursor->content);
			cursor->content = var_content;
			break ;
		}
		cursor = cursor->next;
	}
}

void	remove_node(t_envp **envp, char *var)
{
	t_envp	*cursor;
	t_envp	*node_temp;

	cursor = *envp;
	while (cursor->next)
	{
		if (cursor->next->title && var && !ft_strcmp(cursor->next->title, var))
		{
			node_temp = cursor->next->next;
			free(cursor->next->title);
			free(cursor->next->content);
			free(cursor->next);
			cursor->next = node_temp;
			break ;
		}
		cursor = cursor->next;
	}
}
