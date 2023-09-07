/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:56:05 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/07 17:26:14 by yoamzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **input)
{
	int		i;
	int		j;
	int		nfalag;

	i = 1;
	nfalag = 0;
	while (input[i] && input[i][0] == '-')
	{
		if (input[i][0] && input[i][0] == '-')
		{
			j = 1;
			while (input[i][j] && input[i][j] == 'n')
				j++;
			if (input[i][j] == '\0')
				nfalag = 1;
			else
			{
				ft_putstr_fd(input[i], 1);
				if (input[i + 1] && ft_strcmp(input[i + 1], " "))
					ft_putchar_fd(' ', 1);
			}
		}
		i++;
	}
	while (input[i])
	{
		if (input[i] && !ft_strcmp(input[i], " "))
			ft_putchar_fd(' ', 1);
		else
		{
			ft_putstr_fd(input[i], 1);
			if (input[i + 1] && ft_strcmp(input[i + 1], " "))
				ft_putchar_fd(' ', 1);
		}
		i++;
	}
	if (nfalag != 1)
		ft_putchar_fd('\n', 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (!s)
	{
		return ;
	}
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
