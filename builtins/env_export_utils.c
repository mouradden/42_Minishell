/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:19:00 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/23 20:05:05 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_back_env(t_envp **head, t_envp *new)
{
	t_envp		*cursor;

	if (*head == NULL)
		*head = new;
	else
	{
		cursor = *head;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = new;
	}
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

void	print_export_error(char *envp)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(envp, 2);
	ft_putstr_fd("`: not a vaaaaalid identifier\n", 2);
}

int	check_title(char *title)
{
	int	i;

	i = 0;
	if (title[i])
	{
		if (title[i] == '_' || (title[i] >= 'a' && title[i] <= 'z')
			|| (title[i] >= 'A' && title[i] <= 'Z'))
			return (1);
	}
	return (0);
}

int	check_identifier(char *tit, char *envp)
{
	if (!check_title(tit))
	{
		print_export_error(envp);
		free(tit);
		return (1);
	}
	return (0);
}
