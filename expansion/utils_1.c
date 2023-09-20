/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:44:00 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/20 22:27:47 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builting(char *cmd)
{
	if (cmd && (!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "pwd")
			|| !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
			|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "export")
			|| !ft_strcmp(cmd, "unset")))
		return (0);
	else
		return (1);
}

int	contains_equal(char *str, int c)
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

int	contains(char *str, int c)
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
