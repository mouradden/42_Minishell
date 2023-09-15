/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:44:00 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/14 15:44:31 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
