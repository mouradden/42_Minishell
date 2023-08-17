/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:56:05 by mdenguir          #+#    #+#             */
/*   Updated: 2023/08/17 13:31:36 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **input)
{
	int		i;
	int		j;
	int		temp;

	i = 1;
	temp = 0;
	while (input[i] && input[i][0] == '-')
	{
		// if (input[i] && !ft_strcmp(input[i], " "))
		// 	i++;
		if (input[i][0] && input[i][0] == '-')
		{
			j = 1;
			while (input[i][j] && input[i][j] == 'n')
				j++;
			if (input[i][j] == '\0')
				temp = 1;
			else
			{
				if (ft_strcmp(input[i], " "))
					ft_putstr_fd(input[i], 1);
				if (input[i + 1])
					ft_putchar_fd(' ', 1);
			}
		}
		i++;
	}
	while (input[i])
	{
		// if (ft_strcmp(input[i], " "))
			ft_putstr_fd(input[i], 1);
		if (ft_strcmp(input[i], " ") && input[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
			// }
			// else
			// {
			// 	while (input[i])
			// 	{
			// 		ft_putstr_fd(input[i], 1);
			// 		i++;
			// 		if (input[i + 1])
			// 			ft_putchar_fd(' ', 1);
			// 	}
			// }
		// }
		// else
		// {
		// 	ft_putstr_fd(input[i], 1);
		// }
		// if (input[i + 1])
		// 	ft_putchar_fd(' ', 1);
	// 	i++;
	// }
	if (temp != 1)
		ft_putchar_fd('\n', 1);
}

// void    echo(char **cmd)
// {
//     int    i;
//     int    nflag;

//     nflag = 0;
//     i = 1;
//     while (cmd[i] != NULL)
//     {
//         if (ft_strcmp(cmd[i], "-n") == 0)
//             nflag = 1;
//         else
//         {
//             printf("%s", cmd[i]);
//             if (cmd[i + 1] != NULL)
//                 printf(" ");
//         }
//         i++;
//     }
//     if (nflag == 0)
//         printf("\n");
// }

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