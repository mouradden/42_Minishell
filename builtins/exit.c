/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:35:55 by yoamzil           #+#    #+#             */
/*   Updated: 2023/09/24 10:05:22 by yoamzil          ###   ########.fr       */
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

void	exit_printing(char *str)
{
	printf("exit: %s: numeric argument required\n", str);
	exit(255);
}

int	num_of_elem(char **args)
{
	int	count;

	count = 0;
	while (args[count] != NULL)
		count++;
	return (count);
}

void	ft_exit(char **args)
{
	int	count;
	int	nbr;

	count = num_of_elem(args);
	if (count == 1)
		exit(0);
	else if (count == 2)
	{
		if (ft_isdigit(args[1]))
		{
			nbr = ft_atoi(args[1]);
			exit(nbr);
		}
		else
			exit_printing(args[1]);
	}
	else if (count > 2)
	{
		if (!ft_isdigit(args[1]))
			exit_printing(args[1]);
		else
			printf("exit: too many arguments\n");
	}
}
