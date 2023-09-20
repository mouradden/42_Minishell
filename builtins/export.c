/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:06:27 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/20 22:25:42 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export(t_envp **envp, char **var)
{
	int		i;
	int		j;
	char	**splitted_var;

	if (!var[1] || !var[1][0])
		display_export(envp);
	else
	{
		i = 1;
		while (var[i])
		{
			if ((contains(var[i], '=') > -1) && contains_equal(var[i], ' '))
			{
				splitted_var = ft_split(var[i], ' ');
				j = 0;
				while (splitted_var[j])
					split_env(envp, splitted_var[j++]);
				free_double(splitted_var);
			}
			else
				split_env(envp, var[i]);
			i++;
		}
	}
	g_exit_status = 0;
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

int	check_duplicate(t_envp **envp, char *var)
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

void	update_node(t_envp **envp, char *var_title, char *var_content)
{
	t_envp	*cursor;

	cursor = *envp;
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
