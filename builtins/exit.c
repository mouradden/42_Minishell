/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:35:55 by yoamzil           #+#    #+#             */
/*   Updated: 2023/09/23 23:49:54 by yoamzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '-' && s[i + 1] >= '0' && s[i + 1] <= '9') 
			|| (s[i] >= '0' && s[i] <= '9'))
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	number;
	int	sign;

	i = 0;
	number = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i + 1] == '+' || str[i + 1] == '-')
			return (0);
		else if (str[i] == '-')
			sign *= (-1);
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return (number * sign);
}

void	ft_exit(char **args)
{
	int	count;
	int	i;
	int	nbr;

	count = 0;
	i = 0;
	while (args[count] != NULL)
		count++;
	if (count == 1)
	{
		printf("exit\n");
		exit(0);
	}
	else if (count == 2)
	{
		if (ft_isdigit(args[1]))
		{
			nbr = ft_atoi(args[1]);
			exit(nbr);
		}
		else
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			exit(255);
		}
	}
	else if (count > 2)
	{
		if (!ft_isdigit(args[1]))
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			exit(255);
		}
		else
			printf("exit: too many arguments\n");
	}
}
