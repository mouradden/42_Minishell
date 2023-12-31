/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:33:02 by yoamzil           #+#    #+#             */
/*   Updated: 2023/09/25 12:17:52 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_output_add(t_redir *redis)
{
	int		fd;

	fd = open(redis->file_name, O_CREAT
			| O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_putstr_fd(redis->file_name, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		exit(1);
	}
	else
		dup2(fd, STDOUT_FILENO);
}

void	dup_output_append(t_redir *redis)
{
	int		fd;

	fd = open(redis->file_name, O_CREAT
			| O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_putstr_fd(redis->file_name, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		exit(1);
	}
	else
		dup2(fd, STDOUT_FILENO);
}

void	dup_input(t_redir *redis)
{
	int		fd;

	if (access(redis->file_name, F_OK) == 0)
	{
		fd = open(redis->file_name, O_RDONLY | S_IRUSR);
		dup2(fd, STDIN_FILENO);
	}
	else
	{
		perror(redis->file_name);
		exit(1);
	}
}

void	dup_herdoc(int *fdd)
{
	if (*fdd != -1 && dup2(*fdd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
}
