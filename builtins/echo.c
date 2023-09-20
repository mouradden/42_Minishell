/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:56:05 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/20 22:19:57 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **input)
{
	int		i;
	int		nflag;

	i = 1;
	nflag = 0;
	check_option_n(input, &i, &nflag);
	print_arg(input, i);
	if (nflag != 1)
		ft_putchar_fd('\n', 1);
	g_exit_status = 0;
}

void	check_option_n(char **input, int *i, int *nflag)
{
	int		j;

	while (input[*i] && input[*i][0] == '-')
	{
		if (input[*i][0] && input[*i][0] == '-')
		{
			j = 1;
			while (input[*i][j] && input[*i][j] == 'n')
				j++;
			if (input[*i][j] == '\0')
				*nflag = 1;
			else
			{
				ft_putstr_fd(input[*i], 1);
				if (input[*i + 1] && ft_strcmp(input[*i + 1], " "))
					ft_putchar_fd(' ', 1);
			}
		}
		(*i)++;
	}
}

void	print_arg(char **input, int i)
{
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
